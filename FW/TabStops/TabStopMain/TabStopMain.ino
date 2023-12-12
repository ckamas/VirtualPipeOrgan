#include <MIDIUSB.h>
#include <Wire.h>

#include "TabStopDriver.h"
#include "TabStopReader.h"
#include "TabStopDataBase.h"

#include "TabStopDriverClass.hpp"
#include "TabStopReaderClass.hpp"

#pragma GCC optimize("-O0")

TabStopsEngine MyEngine;
int drive = 0;
unsigned long timeout;

TabStopsReadingEngine MyTabReader;

void MidiCheckControl() {

  midiEventPacket_t control;

  do {
    control = MidiUSB.read();
    if (control.header != 0) {
      timeout = millis();
      digitalWrite(LED_BUILTIN, HIGH);
      byte cmd = control.byte1 & 0xf0;
      byte chan = control.byte2 - 1;


      // Serial.print("Received: ");
      // Serial.print(control.header, HEX);
      // Serial.print("-");
      // Serial.print(control.byte1, HEX);
      // Serial.print("-");
      // Serial.print(control.byte2, HEX);
      // Serial.print("-");
      // Serial.println(control.byte3, HEX);

      // https://hauptwerkhardware.com/downloads/MotorizedStopControllerManual.pdf
      // tab stop delta on/off = note on/off midi message event on=9X,off=8x note
      // calibration: pulse note on and off five times measuring the delta time. store value + fudge factor in eeprom

      // https://www.organworks.com/Documents/MLRT-1%20Installation%20Manual%20v1.1.pdf
      // A Tab-On gives (0xBn 0x51 xx), where 'xx' is the tab number from 0 to 127 and 'n' is the Channel (0 to 15).
      // Tab-Off gives (0xBn 0x50 xx)
      // Lamp-On is (0xBn 0x51 xx), where 'xx' is the lamp number from 0 to 127 and 'n' is the Channel (0 to 15).
      // Lamp-Off is (0xBn 0x50 xx). All Lamps Off uses (Bn 79 00) (0x79=121, reset all controllers) or (FF)

      // https://www.midi.org/specifications-old/item/table-1-summary-of-midi-message

      switch (cmd) {
        case 0x90:
        case 0x51:
          {
            // turn tab on
            MyEngine.tabOn(chan);
            break;
          }
        case 0x80:
        case 0x50:
          {
            MyEngine.tabOff(chan);
            break;
          }
      }
    }
  } while (control.header != 0);
}


void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  Wire.begin();

  setupTabStopDriver();
  setupTabStopReader();

  MyEngine.init();
  timeout = millis();

  // Serial.print("Stops Size=");
  // Serial.println(stopsSize, DEC);

  MyTabReader.init();

  light(PowerLight, on);
}



void loop() {
  if (millis() - timeout >= 250) {
    timeout = millis();
    digitalWrite(LED_BUILTIN, LOW);
  }
  MidiCheckControl();
  MyEngine.loop();
  MyTabReader.loop();
}

// if (millis() - timeout >= 250) {
//   timeout = millis();
//   MyEngine.tabOn(drive);
//   drive++;
//   if (stops[drive].I2C_BIT == -1 && stops[drive].SPIaddress == -1) {
//     drive = 0;
//   }
//   MyEngine.tabOff(drive);
//   // scanTabsPrintCode();
//   // Serial.println(".");
// }


// int mux = 7;
// bool printed = false;
// for (int chip = 0; chip < 7; chip++) {
//   for (int bit = 0; bit < 8; bit++) {
//     int address = mux << 6 | chip << 3 | bit;
//     // address=0x1c8;
//     if (isTabSet(address) == 1) {
//       printed = true;
//       Serial.print(stops[i].SPIaddress);
//       Serial.print(" 0x");
//       Serial.print(address, HEX);
//       Serial.print(" ");
//       Serial.print(stops[i].TabStop);
//       Serial.print(" ");
//     }
//   }
// }
// if (printed) {
//   Serial.println();
//   printed = false;
// }
