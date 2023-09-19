#include "NewSpiShiftRegisterChain.h"
#include <SPI.h>

#define numBoards 20
NewSpiShiftRegisterChain my595(10, numBoards);

void setupTabStopDriver (void)
{
  SPI.begin();
  my595.setDataToZeros();
  my595.writeData();
}


static void DriveOn (unsigned int bit)
{
  unsigned int board=bit>>3;
  unsigned int pin=bit&0x7;
  return my595.setBitOn((board<<3)+(7-pin));
}

static void DriveOff (unsigned int bit)
{
  unsigned int board=bit>>3;
  unsigned int pin=bit&0x7;
  return my595.setBitOff((board<<3)+(7-pin));
}

void TabPulseOff (int tab, int pause)
{
  const int TABA = 0;
  const int TABB = 1;

  int i=tab*2;

  // turn on a and off b
  DriveOn(TABA + i);
  DriveOff(TABB + i);
  delay(pause);

  // turn off a
  DriveOff(TABA + i);
}

void TabPulseOn (int tab, int pause)
{
  const int TABA = 0;
  const int TABB = 1;

  int i=tab*2;

  // turn DriveOn b and off a
  DriveOn(TABB + i);
  DriveOff(TABA + i);
  delay(pause);
  
  // turn off b
  DriveOff(TABB + i);
}

// void loop() {
//   // put your main code here, to run repeatedly:
//   int i=0;
//   while (Pedal[i].address>=-99)
//   {
//     Serial.print("Turning (");
//     Serial.print(i);
//     Serial.print(") on @ Address=");
//     Serial.println(Pedal[i].address);

//     onDelay (&my595,Pedal[i].address,100);
//     i++;
//   }
//   delay(1000);

//   i=0;
//   while (Pedal[i].address>=-99)
//   {
//     Serial.print("Turning (");
//     Serial.print(i);
//     Serial.print(") off @ Address=");
//     Serial.println(Pedal[i].address);

//     offDelay (&my595,Pedal[i].address,100);
//     i++;
//   }

//   delay(1000);

// }
