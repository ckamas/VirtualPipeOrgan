#include "variant.h"
#include <Arduino.h>
#include <MIDIUSB.h>

#include "TabStopDataBase.h"
#include "TabStopReaderClass.hpp"
#include "TabStopReader.h"

#pragma GCC optimize("-O0")


void TabStopsReadingEngine::MidiSendTabOn(uint8_t tab) {

  const byte velocity = 0;
  const byte channel = 2;

  // First parameter is the event type (0x09 = note on, 0x08 = note off).
  // Second parameter is note-on/note-off, combined with the channel.
  //  Channel can be anything between 0-15. Typically reported to the user as 1-16.
  // Third parameter is the note number (48 = middle C).
  // Fourth parameter is the velocity (64 = normal, 127 = fastest).
  midiEventPacket_t noteOn = { 0x09, 0x90 | channel, tab, velocity };

  MidiUSB.sendMIDI(noteOn);
  MidiUSB.flush();

  Serial.print("MIDI Setting tab ");
  Serial.print(tab);
  Serial.println(" to on");
}

void TabStopsReadingEngine::MidiSendTabOff(uint8_t tab) {

  const byte velocity = 0;
  const byte channel = 2;

  // First parameter is the event type (0x09 = note on, 0x08 = note off).
  // Second parameter is note-on/note-off, combined with the channel.
  //  Channel can be anything between 0-15. Typically reported to the user as 1-16.
  // Third parameter is the note number (48 = middle C).
  // Fourth parameter is the velocity (64 = normal, 127 = fastest).
  midiEventPacket_t noteOff = { 0x08, 0x80 | channel, tab, velocity };

  MidiUSB.sendMIDI(noteOff);
  MidiUSB.flush();

  Serial.print("MIDI Setting tab ");
  Serial.print(tab);
  Serial.println(" to off");
}


void TabStopsReadingEngine::init() {
  myDatabase[0] = { .mux = 6, .chip = 0, .value = 0 };
  myDatabase[1] = { .mux = 6, .chip = 1, .value = 0 };
  myDatabase[2] = { .mux = 7, .chip = 0, .value = 0 };
  myDatabase[3] = { .mux = 7, .chip = 1, .value = 0 };
  myDatabase[4] = { .mux = 7, .chip = 2, .value = 0 };
  myDatabase[5] = { .mux = 7, .chip = 3, .value = 0 };
  myDatabase[6] = { .mux = 7, .chip = 4, .value = 0 };
  myDatabase[7] = { .mux = 7, .chip = 5, .value = 0 };
  myDatabase[8] = { .mux = 7, .chip = 6, .value = 0 };
  myDatabase[9] = { .mux = 7, .chip = 7, .value = 0 };
}

void TabStopsReadingEngine::TabStopsReadingEngineDebug() {
  for (int i = 0; i < NumDevices; i++) {
    Serial.print(i);
    Serial.print("=");
    if (myDatabase[i].value < 16) Serial.print("0");
    Serial.print(myDatabase[i].value, HEX);
    Serial.print(" ");
  }
  Serial.println("");
}

void TabStopsReadingEngine::loop() {

  // for (;;) {
  // scanTabs();
  // delay (500);
  // }


  // read all of the i2c devices to see the state of the tabs
  for (int i = 0; i < NumDevices; i++) {
    uint8_t mux = myDatabase[i].mux;
    uint8_t chip = myDatabase[i].chip;
    uint8_t x = readPCF8574(mux, chip);

    // //debug
    // if (x != myDatabase[i].value) {
    //   Serial.print("Mux=");
    //   Serial.print(mux);
    //   Serial.print(" Chip=");
    //   Serial.print(chip);
    //   Serial.print(" x=0x");
    //   Serial.print(x, HEX);
    //   Serial.print(" value=0x");
    //   Serial.println(myDatabase[i].value, HEX);
    // }  //~debug

    myDatabase[i].value = x;
  }

#define DEBOUNCE 100  // debounce time

  // now loop through all of the TabStops checking if they are in a new state, if so send the midi message
  for (int stops_i = 0; stops_i < stopsSize; stops_i++) {
    // now check the time out for timeded outed
    if (stops[stops_i].ReadTimeStamp != 0) {
      if (millis() - stops[stops_i].ReadTimeStamp >= DEBOUNCE) {
        stops[stops_i].ReadTimeStamp = 0;
      }
    }

    int tabAddress = stops[stops_i].I2C_BIT;
    uint8_t mux = (tabAddress >> 6) & 0x07;
    //Serial.print ("Mux="); Serial.println(mux);
    int chip = (tabAddress >> 3) & 0x07;
    //Serial.print ("Chip="); Serial.println(chip);
    int bit = tabAddress & 0x07;
    //Serial.print ("bit="); Serial.println(bit);

    for (int database_i = 0; database_i < NumDevices; database_i++) {

      if (myDatabase[database_i].mux == mux && myDatabase[database_i].chip == chip) {
        if (myDatabase[database_i].value & (1 << bit)) {  // i2c read the tab as set...
          if (stops[stops_i].tabReadSet) {
            // we both are on, so do nothing
          } else {
            // now check the time out for reset
            if (stops[stops_i].ReadTimeStamp == 0) {
              stops[stops_i].ReadTimeStamp = millis();
              if (stops[stops_i].ReadTimeStamp == 0) {
                stops[stops_i].ReadTimeStamp = 1;
              }
              MidiSendTabOn(stops_i);  // 1st time we have a new value, let the midi know
              stops[stops_i].tabReadSet = true;
              // TabStopsReadingEngineDebug();
            }
          }
        } else {  // i2c read the tab as NOT set
          if (stops[stops_i].tabReadSet) {
            // now check the time out for reset
            if (stops[stops_i].ReadTimeStamp == 0) {
              stops[stops_i].ReadTimeStamp = millis();
              if (stops[stops_i].ReadTimeStamp == 0) {
                stops[stops_i].ReadTimeStamp = 1;
              }
              MidiSendTabOff(stops_i);  // 1st time we have a new value, let the midi know
              stops[stops_i].tabReadSet = false;
              // TabStopsReadingEngineDebug();
            }
          } else {
            // we both are off, so do nothing
          }
        }
        break;  // found our match, escape!

      }  //if (myDatabase[database_i].mux == mux && myDatabase[database_i].chip == chip)

    }  // for (int database_i = 0; database_i < NumDevices; database_i++)

  }  //for (int stops_i = 0; stops_i < stopsSize; stops_i++) {
  MidiUSB.flush();
}  // loop()