#include "TabStopDriver.h"
#include "TabStopReader.h"
#include "TabStopDataBase.h"

#include "TabStopDriverClass.hpp"

#pragma GCC optimize("-O0")


void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  setupTabStopDriver();
  setupTabStopReader();
}

void loop() {
  TabStopsEngine MyEngine;
  MyEngine.init();

  int drive = 0;
  unsigned long timeout = millis();

  for (;;) {
    if (millis() - timeout >= 25) {
      timeout = millis();
      MyEngine.tabOn(drive);
      drive++;
      if (stops[drive].I2C_BIT == -1 && stops[drive].SPIaddress == -1) {
        drive = 0;
      }
      MyEngine.tabOff(drive);
    }
    MyEngine.loop();
  }
}

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
