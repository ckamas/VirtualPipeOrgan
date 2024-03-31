#include <Arduino.h>
#include <MCP23017.h>
#include <MIDIUSB.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)


MCP23017 A = MCP23017(0x23);
MCP23017 B = MCP23017(0x25);
MCP23017 C = MCP23017(0x26);
MCP23017 D = MCP23017(0x27);

const int CHOIR = 7;
const int GREAT = 6;
const int SWELL = 5;
const int PEDAL = 4;
const int PISTON = 3;

const int CHOIRMIDICHANNEL = 1;
const int GREATMIDICHANNEL = 2;
const int SWELLMIDICHANNEL = 3;
const int PEDALMIDICHANNEL = 4;

enum keyStatus {
  UP = 1,
  DOWN = 2,
};

struct keyState {
  enum keyStatus oldState;
  int midiKey;
};

const int numManualKeys = 61;
//const int numManualKeys = 1;
const int numPedalKeys = 32;
const int lowestManualNoteMIDI = 36;
const int lowestPedalNoteMIDI = 12;  // I think 24 is CC not CCC... might need to be 12 notes lower, or 12 for CCC!

struct keyState choirKeys[numManualKeys];
struct keyState greatKeys[numManualKeys];
struct keyState swellKeys[numManualKeys];
struct keyState pedalKeys[numManualKeys];




/////////////////////////////////////////////
///// init code ////////////////////////////
///////////////////////////////////////////
void initKeyState(struct keyState *keys, int length, int startNote) {
  for (int i = 0; i < length; i++) {
    keys[i].oldState = UP;
    keys[i].midiKey = i + startNote;  // 36 is the lowest note on an organ manual
  }
}

void setup() {
  Wire.begin();
  Wire.setClock(400000L);
  Serial.begin(115200);
  while (!Serial) {};
  Serial.println("Hello World");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  //  Serial.println(TOSTRING(__LINE__));

  // setup the select pins
  pinMode(CHOIR, OUTPUT);
  pinMode(GREAT, OUTPUT);
  pinMode(SWELL, OUTPUT);
  pinMode(PEDAL, OUTPUT);
  pinMode(PISTON,OUTPUT);
  //  Serial.println(TOSTRING(__LINE__));

  digitalWrite(CHOIR, HIGH);
  digitalWrite(GREAT, HIGH);
  digitalWrite(SWELL, HIGH);
  digitalWrite(PEDAL, HIGH);
  digitalWrite(PISTON, HIGH);
  //  Serial.println(TOSTRING(__LINE__));

  A.init();
  B.init();
  C.init();
  D.init();
  //  Serial.println(TOSTRING(__LINE__));

  A.portMode(MCP23017Port::A, 0xff, 0xff, 0xff);
  A.portMode(MCP23017Port::B, 0xff, 0xff, 0xff);
  B.portMode(MCP23017Port::A, 0xff, 0xff, 0xff);
  B.portMode(MCP23017Port::B, 0xff, 0xff, 0xff);
  C.portMode(MCP23017Port::A, 0xff, 0xff, 0xff);
  C.portMode(MCP23017Port::B, 0xff, 0xff, 0xff);
  D.portMode(MCP23017Port::A, 0xff, 0xff, 0xff);
  D.portMode(MCP23017Port::B, 0xff, 0xff, 0xff);
  //  Serial.println(TOSTRING(__LINE__));

  // setup the key database
  initKeyState(choirKeys, numManualKeys, lowestManualNoteMIDI);
  initKeyState(greatKeys, numManualKeys, lowestManualNoteMIDI);
  initKeyState(swellKeys, numManualKeys, lowestManualNoteMIDI);
  initKeyState(pedalKeys, numManualKeys, lowestPedalNoteMIDI);
  //  Serial.println(TOSTRING(__LINE__));
}


/////////////////////////////////////////////////
///////////Helper funcitons ////////////////////
////////////////////////////////////////////////
void readManual(int manual, uint64_t *keys) {
  digitalWrite(manual, LOW);
  //delayMicroseconds(50);  // wait Xus

  *keys = A.read();
  *keys = *keys << 16 | B.read();
  *keys = *keys << 16 | C.read();
  *keys = *keys << 16 | D.read();

  digitalWrite(manual, HIGH);
}

// midi status messages:
//Message Type    MS Nybble LS Nybble Number of Data Bytes  Data Byte 1        Data Byte 2
//Note Off        0x8       Channel   2                     Note Number        Velocity
//Note On         0x9       Channel   2                     Note Number        Velocity
//Control Change  0xB       Channel   2                     Controller Number  Value

// midi control change used for analog...
// chanel 0-15
// control 0-128
// value 0-128
void sendMidiAnalog(uint8_t channel, uint8_t control, uint8_t value) {
  midiEventPacket_t event = { 0x0B, (uint8_t)(0xB0 | channel), control, value };
  MidiUSB.sendMIDI(event);
  MidiUSB.flush();
}

// chanel 0-15
// note 0-128
// noteOnOff, 0= note off, 1=note on
void sendMidiNoteOn(uint8_t channel, uint8_t note) {
  midiEventPacket_t noteOn = { 0x09, (uint8_t)(0x90 | channel), note, 0x40 };
  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();
}

void sendMidiNoteOff(uint8_t channel, uint8_t note) {
  midiEventPacket_t noteOff = { 0x09, (uint8_t)(0x80 | channel), note, 0x00 };
  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();
}


// void dumpKeyState(struct keyState *keysState)
// {
//  Serial.print("\tAddress="); Serial.println((int)keysState);
//  Serial.print("\toldState="); Serial.println(keysState[0].oldState);
//  Serial.println("\tmidiKey="); Serial.println(keysState[0].midiKey);
// }

void UpadateKeyState(struct keyState *keysState, uint64_t keys, int length, int midiChannel) {
    // Serial.println(TOSTRING(__LINE__));
    // dumpKeyState(keysState);
  for (int i = 0; i < length; i++) {
    int state = 0;

    state = (keys >> (uint64_t)i) & 0x01;

    if (state)  // key is pressed
    {
      if (UP == keysState[i].oldState)  // old was up, now down
      {
        keysState[i].oldState = DOWN;
        sendMidiNoteOn(midiChannel, keysState[i].midiKey);  // turn on note
                                                                    Serial.print ("ON. i="); Serial.print (i); Serial.print (" midiChannel="); Serial.print (midiChannel); Serial.print (" key#="); Serial.print ( keysState[i].midiKey); Serial.println();
                                                            //        Serial.print(TOSTRING(__LINE__));
                                                            //        dumpKeyState(keysState);
      }
    } else {
      if (DOWN == keysState[i].oldState)  // old was downn, now up
      {
        keysState[i].oldState = UP;
        sendMidiNoteOff(midiChannel, keysState[i].midiKey);  // turn off note
                                                                     Serial.print ("OFF i="); Serial.print (i); Serial.print (" midiChannel="); Serial.print (midiChannel); Serial.print (" key#="); Serial.print ( keysState[i].midiKey); Serial.println();
                                                             //        Serial.print(TOSTRING(__LINE__));
                                                             //        dumpKeyState(keysState);
      }
    }
  }
}

///////////////////////////////////////////////////////
///////////// main loop ///////////////////////////////
///////////////////////////////////////////////////////
void loop() {
  // put your main code here, to run repeatedly:

#if 0
  // MidiUSB.poll();

  while (MidiUSB.available()) {
    // We must read entire available data, so in case we receive incoming
    // MIDI data, the host wouldn't get stuck.
    MidiUSB.read(); // we don't care about incoming midi, so just drop it!
  }
#endif

  uint64_t keys;

  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)

  readManual(CHOIR, &keys); // 11 ms
  UpadateKeyState(choirKeys, keys, numManualKeys, CHOIRMIDICHANNEL); //0.620 msZ

  readManual(GREAT, &keys);
  UpadateKeyState(greatKeys, keys, numManualKeys, GREATMIDICHANNEL);

  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW

  readManual(SWELL, &keys);
  UpadateKeyState(swellKeys, keys, numManualKeys, SWELLMIDICHANNEL);

  readManual(PEDAL | PISTON, &keys);
  UpadateKeyState(pedalKeys, keys, numManualKeys, PEDALMIDICHANNEL);

  //  delay(1000);                       // wait for a second
}
