#include <Arduino.h>
#include <Wire.h>
#include <PCF8574.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>  //Click here to get the library: http://librarymanager/All#SparkFun_I2C_Mux
#include <MIDIUSB.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT __FILE__ ":" TOSTRING(__LINE__)

QWIICMUX myMux;

PCF8574 PCF[8] = {
  PCF8574(0x20, &Wire),
  PCF8574(0x21, &Wire),
  PCF8574(0x22, &Wire),
  PCF8574(0x23, &Wire),
  PCF8574(0x24, &Wire),
  PCF8574(0x25, &Wire),
  PCF8574(0x26, &Wire),
  PCF8574(0x27, &Wire)
};

void setup() {
  // put your setup code here, to run once:
  Wire.begin();

  Serial.begin(115200);
  while (!Serial) {};

  Serial.println("Hello World");

  Serial.println(__FILE__);
  Serial.print("PCF8574_LIB_VERSION:\t");
  Serial.println(PCF8574_LIB_VERSION);

  if (myMux.begin() == false) {
    Serial.println("Mux not detecte");
    //while (1);
  }
  Serial.println("Mux detected");


  // scan the mux's ports for PCF8574s
  for (int m = 0; m <= 7; m++) {
    //Serial.print("Setting MUX to :");
    //Serial.println(m);

    myMux.setPort(m);  //Connect master to port m on the mux
    Serial.print("M:");
    Serial.print(m);
    Serial.print("-> ");

    for (int n = 0; n <= 7; n++) {
      Serial.print(n);
      Serial.print(":");
      PCF[n].begin(0xff); // from the data sheet: The I/Os should be high before being used as inputs.
      PCF[n].write8(0xff);  // drive it back to 0v so that the cap can discharge in the protection circuit
      if (!PCF[n].isConnected()) {
        Serial.print((".. "));
      } else {
        int x = PCF[n].read8();
        if (x < 16) Serial.print("0");
        Serial.print(x, HEX);
        Serial.print(" ");
      }
    }  // for n
    Serial.println("");
  }  // for m
}

int readPCF8574(uint8_t mux, uint8_t address) {
  if (mux > 7) {
    Serial.print("BAD call to ");
    Serial.print(__FUNCTION__);
    Serial.print(" with mux set to ");
    Serial.println(mux);
    return -1;
  }
  if (address > 7) {
    Serial.print("BAD call to ");
    Serial.print(__FUNCTION__);
    Serial.print(" with address set to ");
    Serial.println(address);
    return -1;
  }

  myMux.setPort(mux);         //Connect master to port 'mux' on the mux
  // don't do this here as it causes a FET to VCC to briefly switch on. This will swamp our readings!
  //PCF[address].write8(0xff);  // from the data sheet: The I/Os should be high before being used as inputs.

  int x = PCF[address].read8();
  int error = PCF[address].lastError();
  if (error != 0 || x < 0) {
    Serial.print("ERROR in reading! MUX:");
    Serial.print(mux);
    Serial.print(" address");
    Serial.print(address);
    Serial.print(" Value:");
    Serial.print(x, HEX);
    Serial.print(" Error:");
    Serial.println(error);
  }
  return x;
}

void loop() {
  for (uint8_t i = 0; i < 8; i++) {
    int x = readPCF8574(7, i);
    if (x >= 0) {
      Serial.print(" ");
      Serial.print(i);
      Serial.print(":0x");
      if (x < 16) Serial.print("0");
      Serial.print(x, HEX);
    }
  }
  Serial.println("");
  delay(1000);
}

#if 0
typedef struct {
//  char keyboard[20];
//  char name[20]; 
  int address;
  int tabStopBIT; // which bit in the readback coresponds to this tabstop
//  int MidiAddr;
} keyBoard;

// tab stop database
    /*Swell 8' Geigen Diapason*/	13,
    /*Swell 8' Rohr flote*/	14,
    /*Swell 8' Salicional*/	15,
    /*Swell 8' Voix Celeste*/	16,
    /*Swell 8' Flute Celests II*/	17,
    /*Swell 4' Prestant*/	18,
    /*Swell 4' Nacht horn*/	19,
    /*Swell 16' Fagotto*/	20,
    /*Swell 8' Trompette*/	21,
    /*Swell 8' Oboe*/	22,
    /*Swell 4' Clairon*/	23,
    /*Swell 16' Swell to Swell*/	24,
    /*Swell Swell Unison Off*/	25,
    /*Swell 4' Swell to Swell*/	26,

    /*Antiphonal Provisions Swell Main Off*/	27,
    /*Antiphonal Provisions Swell Antiphonal On*/	28,
    /*Antiphonal Provisions Great/Choir Main Off*/	40,
    /*Antiphonal Provisions Great/Choir Antiphonal On*/	39,

    /*Antiphonal Provisions ?*/	29,

    /*Choir 8' Viola*/	43,
    /*Choir 8' Gedeckt*/	44,
    /*Choir 8' Quintade (w/chiff)*/	45,
    /*Choir 8' Dulciana*/	46,
    /*Choir 4' Principal*/	47,
    /*Choir 4' Koppelflote*/	48,
    /*Choir 4' Quintadena (w/chiff)*/	49,
    /*Choir 2-2/3' Nazard*/	50,
    /*Choir 2' Flachflote*/	51,
    /*Choir 1-3/5' Tierce*/	52,
    /*Choir 1' Sifflote*/	53,
    /*Choir Harp*/	54,
    /*Choir Carillon*/	55,
    /*Choir 16' Choir to Choir*/	70,
    /*Choir Choir to Unison Off*/	71,
    /*Choir 4' Choir to Choir*/	72,
    /*Choir 16' Swell to Choir*/	73,
    /*Choir 8' Swell to Choir*/	42,
    /*Choir 4' Swell to Choir*/	41,

    /*Pedal: 32' Contra Violone*/ -1,
    /*Pedal: 16' Principal*/	59,
    /*Pedal: 16' Bourdon*/	60,
    /*Pedal: 16' Lieblich Gedeckt*/	61,
    /*Pedal: 16' Dulciana*/	62,
    /*Pedal: 8' Octave*/	63,
    /*Pedal: 8' Flute*/	64,
    /*Pedal: 8' Gemshorn*/	65, // 1/2 not working
    /*Pedal: 4' Choralbass*/	66,
    /*Pedal: 16' Bombarde*/	67,
    /*Pedal: 8' Trompette (sw)*/	68,
    /*Pedal: 4' Clairon (sw)*/	69,
    /*Pedal: 8' Great to Pedal*/	30,
    /*Pedal: 4' Great to Pedal*/	31,
    /*Pedal: 8' Swell to Pedal*/	32,
    /*Pedal: 4' Swell to Pedal*/	33,
    /*Pedal: 8' Choir to Pedal*/	34,
    /*Pedal: 4' Choir to Pedal*/	35,

    /*Tremulants Main Tremulant*/	38,
    /*Tremulants Flute Tremulant-Light*/	37,
    /*Tremulants Flute Tremulant-Full*/	36,

    /*Great 16' Gemshorn*/	12,
    /*Great 8' Principal*/	11,
    /*Great 8' Bourdon*/	10,
    /*Great 4' Octave*/	9,
    /*Great 4' Spitz flote*/	8,
    /*Great 2-2/3' Twelfth*/	7,
    /*Great 2' Super Octave*/	6,
    /*Great 2' Blockflote*/	5,
    /*Great Mixture III*/	4,
    /*Great 4' Great to Great*/	3,
    /*Great 16' Swell to Great*/	2,
    /*Great 8' Swell to Great*/	1,
    /*Great 4' Swell to Great*/	0,
    /*Great 16' Choir to Great*/	56,
    /*Great 8' Choir to Great*/	57,
    /*Great 4' Choir to Great*/	58,
#endif