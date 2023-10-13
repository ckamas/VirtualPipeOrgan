#include <Arduino.h>
#include "TabStopDataBase.h"
#include "TabStopDriverClass.hpp"
#include "TabStopReader.h"
#include "TabStopDriver.h"


// TabStopsEngine all drivers off, leave in their current position.
TabStopsEngine::~TabStopsEngine() {
  for (int i = 0; stops[i].I2C_BIT != -1 && stops[i].SPIaddress != -1; i++) {
    TabOff(i);
  }
}

// drive all tabs to the "off" position
void TabStopsEngine::init() {
  for (int i = 0; stops[i].I2C_BIT != -1 && stops[i].SPIaddress != -1; i++) {
    tabOff(i);
    stops[i].MyState = standby;
  }
}

const int DRIVETIME = 200;  // drive for n milliseconds

// update the tab data base
// looking for tabs that are being driven and are wating for their timeout to
// stop driving
void TabStopsEngine::loop() {

  // look through the data base for stops that need to be moved or are done
  for (int i = 0; stops[i].I2C_BIT != -1 && stops[i].SPIaddress != -1; i++) {
    switch (stops[i].MyState) {
      case standby:
        // do nothing
        break;

      case start_on:
        // Serial.print("Turing tab");
        // Serial.print(i);
        // Serial.println(" on");

        TabSetOn(i);
        stops[i].timestamp = millis();
        stops[i].MyState = wait_on;
        break;

      case start_off:
        // Serial.print("Turing tab");
        // Serial.print(i);
        // Serial.println(" off");

        TabSetOff(i);
        stops[i].timestamp = millis();
        stops[i].MyState = wait_off;
        break;

      case wait_on:
        if (millis() - stops[i].timestamp >= DRIVETIME) {
          // Serial.print("done driving tab");
          // Serial.print(i);
          // Serial.println(" on");

          TabOff(i);
          stops[i].MyState = standby;
        }
        break;

      case wait_off:
        if (millis() - stops[i].timestamp >= DRIVETIME) {
          // Serial.print("done driving tab");
          // Serial.print(i);
          // Serial.println(" off");

          TabOff(i);
          stops[i].MyState = standby;
        }
        break;
    }
  }
}

// command  TAB on or off
void TabStopsEngine::tabOn(int tab) {
  // if (isTabSet(stops[tab].I2C_BIT) != TABON) {
    // Tab needs to be moved
    stops[tab].MyState = start_on;
  // } else {
  //   // Serial.println("Tab DOES NOT need to be moved on");
  // }
}
void TabStopsEngine::tabOff(int tab) {
  // if (isTabSet(stops[tab].I2C_BIT) != TABOFF) {
    // Tab needs to be moved
    stops[tab].MyState = start_off;
  // } else {
  //   // Serial.println("Tab DOES NOT need to be moved off");
  // }
}
