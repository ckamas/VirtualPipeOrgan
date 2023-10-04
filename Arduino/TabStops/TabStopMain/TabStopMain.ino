#include "TabStopDriver.h"
#include "TabStopReader.h"
#include "TabStopDataBase.h"
#include "TabStopOptimalDrive.h"

#pragma GCC optimize ("-O0")

void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  setupTabStopDriver();
  setupTabStopReader();

  // while (1) {
  //   TabPulseOn(1, 100);
  //   TabPulseOff(1, 100);
  // }

  // for (int i = 0; i < 74; i++) {
  //   TabSetOff(i);
  //   delay(100);
  //   TabOff(i);
  // }

  for (int i = 0;stops[i].I2C_BIT!=-1 && stops[i].SPIaddress!=-1; i++) {
    TabStopOptimalOff(i);
  }


}

void loop() {
  for (int i = 0;stops[i].I2C_BIT!=-1 && stops[i].SPIaddress!=-1; i++) {
    // int i=1; {
    TabStopOptimalOn(i);
    delay(1050);
    TabStopOptimalOff(i);
    delay(1050);
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
