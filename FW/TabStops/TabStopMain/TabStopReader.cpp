#include <Arduino.h>
#include <Wire.h>
#include <PCF8574.h>
#include <SparkFun_I2C_Mux_Arduino_Library.h>  //Click here to get the library: http://librarymanager/All#SparkFun_I2C_Mux
#include <MIDIUSB.h>

#pragma GCC optimize("-O0")

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

void scanTabs(void) {
  // scan the mux's ports for PCF8574s
  for (int m = 0; m <= 7; m++) {
    myMux.setPort(m);  //Connect master to port m on the mux
    Serial.print("M:");
    Serial.print(m);
    Serial.print("-> ");

    for (int n = 0; n <= 7; n++) {
      Serial.print(n);
      Serial.print(":");
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


void scanTabsPrintCode(void) {
  // scan the mux's ports for PCF8574s
  for (int m = 0; m <= 7; m++) {
    myMux.setPort(m);  //Connect master to port m on the mux

    for (int n = 0; n <= 7; n++) {
      if (PCF[n].isConnected()) {
        int x = PCF[n].read8();
        for (int i=0;i<8;i++){
          if (x&(1<<i))
          {
            int code=((m&7)<<6)|((n&7)<<3)|(i&7);
            Serial.print("0X");
            Serial.print(code,HEX);
            Serial.print(" ");
          }
        }
      }
    }  // for n
  }  // for m
}



void setupTabStopReader() {
  // put your setup code here, to run once:

  //  Serial.println(__FILE__);
  //  Serial.print("PCF8574_LIB_VERSION:\t");
  //  Serial.println(PCF8574_LIB_VERSION);

  if (myMux.begin() == false) {
    Serial.println("Mux not detecte");
    //while (1);
  }
  //  Serial.println("Mux detected");


  // scan the mux's ports for PCF8574s
  for (int m = 0; m <= 7; m++) {
    myMux.setPort(m);  //Connect master to port m on the mux
    for (int n = 0; n <= 7; n++) {
      PCF[n].begin(0xff);   // from the data sheet: The I/Os should be high before being used as inputs.
      PCF[n].write8(0xff);  // drive it back to 0v so that the cap can discharge in the protection circuit
    }                       // for n
    Serial.println("");
  }  // for m
  scanTabs();
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

  myMux.setPort(mux);  //Connect master to port 'mux' on the mux
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

int isTabSet(int tabAddress)  // bits 8,7,6 mux, bits 5,4,3 are the chip, bits 2,1,0 are the bit
{
  int mux = (tabAddress >> 6) & 0x07;
  //Serial.print ("Mux="); Serial.println(mux);
  int chip = (tabAddress >> 3) & 0x07;
  //Serial.print ("Chip="); Serial.println(chip);
  int x = readPCF8574(mux, chip);
  int bit = tabAddress & 0x07;
  //Serial.print ("bit="); Serial.println(bit);
  if (x & (1 << bit))
    return 1;
  return 0;
}
