#include "api/Common.h"
#include "USB/USBAPI.h"
#include "variant.h"
#include "TabStopReader.h"
#include "TabStopDataBase.h"
#include "TabStopDriver.h"
#include <Arduino.h>
#pragma GCC optimize("-O0")

// code to turn on the On or Off solenoid until the tab changes state then leave
const int TABOFF = 0;
const int TABON = 1;

void static TabStopOptimalDrive(int index, int state) {

  scanTabsPrintCode();
  Serial.print("-> 0x");
  Serial.print(stops[index].I2C_BIT, HEX);
  Serial.print(" ");
  Serial.print(stops[index].TabStop);
  Serial.print("--> ");


  // it takes ~20ms to move a tab

  // only drive iff it is already in the wrong state
  if (isTabSet(stops[index].I2C_BIT) != state) {
    Serial.print(stops[index].TabStop);
    Serial.print("--> ");
    Serial.println("Tab needs to be moved ");
  }
  else {
    Serial.print(stops[index].TabStop);
    Serial.print("--> ");
    Serial.println("Tab DOES NOT need to be moved ");
  }
  {
    if (state == TABON) {
      TabSetOn(index);
    } else {
      TabSetOff(index);
    }

    delay(10);  // Some time to make sure the mechanics are done moving


    int loop = 50;
    while ((isTabSet(stops[index].I2C_BIT) != state) && --loop) {
      delay(1);
    }
    Serial.print("Loops=");
    Serial.println(loop);
    delay(60);  // Some time to make sure the mechanics are done moving (17 appears to be the min that works, for a total of about 50ms pulse)
    // some other tabs see to only work at 60+ms!
    //delay(500);
    TabOff(index);
  }
}
void TabStopOptimalOn(int index) {
  // Serial.print("on  ");
  TabStopOptimalDrive(index, TABON);
}

void TabStopOptimalOff(int index) {
  // Serial.print("off ");
  TabStopOptimalDrive(index, TABOFF);
}
