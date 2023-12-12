#include "NewSpiShiftRegisterChain.h"
#include <SPI.h>
#include "TabStopDataBase.h"

#define numBoards 20
NewSpiShiftRegisterChain my595(10, numBoards);

void setupTabStopDriver(void) {
  SPI.begin();
  my595.setDataToZeros();
  my595.writeData();
}


static void DriveOn(unsigned int bit) {
  unsigned int board = bit >> 3;
  unsigned int pin = bit & 0x7;
  return my595.setBitOn((board << 3) + (7 - pin));
}

static void DriveOff(unsigned int bit) {
  unsigned int board = bit >> 3;
  unsigned int pin = bit & 0x7;
  return my595.setBitOff((board << 3) + (7 - pin));
}

void light(unsigned int light, bool state) {
  if (state) {
    return my595.setBitOn(light);
  } else {
    return my595.setBitOff(light);
  }
}

const int TABA = 0;
const int TABB = 1;


void TabSetOff(int index) {
  int tab = stops[index].SPIaddress;
  int i = tab * 2;

  // turn on a and off b
  DriveOff(TABB + i);
  DriveOn(TABA + i);
}

void TabSetOn(int index) {
  int tab = stops[index].SPIaddress;
  int i = tab * 2;

  // turn Drive On b and off a
  DriveOff(TABA + i);
  DriveOn(TABB + i);
}

void TabOff(int index) {
  int tab = stops[index].SPIaddress;
  int i = tab * 2;

  // turn Drive off b and a
  DriveOff(TABB + i);
  DriveOff(TABA + i);
}
