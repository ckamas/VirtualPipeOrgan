#include "TabStopDriver.h"
#include "TabStopReader.h"

typedef struct {
 const int SPIaddress;
 const int I2C_BIT;
// int MidiAddr;
const char *TabStop;
} keyBoard;

keyBoard Pedal[]=
{
13,0x1F3,	 " Swell 8 foot Geigen Diapason", 
14,0x1F4,	 " Swell 8' Rohr flote", 
15,0x1F5,	 " Swell 8' Salicional", 
16,0x1F6,	 " Swell 8' Voix Celeste", 
17,0x1F7,	 " Swell 8' Flute Celests II", 
18,0x1E8,	 " Swell 4' Prestant", 
19,0x1E9,	 " Swell 4' Nacht horn", 
20,0x1EA,	 " Swell 16' Fagotto", 
21,0x1EB,	 " Swell 8' Trompette", 
22,0x1EC,	 " Swell 8' Oboe", 
23,0x1ED,	 " Swell 4' Clairon", 
24,0x1EE,	 " Swell 16' Swell to Swell", 
25,0x1EF,	 " Swell Swell Unison Off", 
26,0x1E0,	 " Swell 4' Swell to Swell", 

27,0x1E1,	 " Antiphonal Provisions Swell Main Off", 
28,0x1E2,	 " Antiphonal Provisions Swell Antiphonal On", 
40,0x1D6,	 " Antiphonal Provisions Great/Choir Main Off", 
39,0x1D5,	 " Antiphonal Provisions Great/Choir Antiphonal On", 

29,	0,	 " Antiphonal Provisions ?", 

43,0x1C7,	 " Choir 8' Viola", 
44,0x1C6,	 " Choir 8' Gedeckt", 
45,0x1C5,	 " Choir 8' Quintade (w/chiff)", 
46,0x1C4,	 " Choir 8' Dulciana", 
47,0x1C3,	 " Choir 4' Principal", 
48,0x1C2,	 " Choir 4' Koppelflote", 
49,0x1C1,	 " Choir 4' Quintadena (w/chiff)", 
50,0x1C0,	 " Choir 2-2/3' Nazard", 
51,0x1CF,	 " Choir 2' Flachflote", 
52,0x1CE,	 " Choir 1-3/5' Tierce", 
53,0x1CD,	 " Choir 1' Sifflote", 
54, 0,	 " Choir Harp", 
55, 0,	 " Choir Carillon", 
70,0x1CC,	 " Choir 16' Choir to Choir", 
71,0x1CB,	 " Choir Choir to Unison Off", 
72,0x1CA,	 " Choir 4' Choir to Choir", 
73,0x1C9,	 " Choir 16' Swell to Choir", 
42,0x1C8,	 " Choir 8' Swell to Choir", 
41,0x1D7,	 " Choir 4' Swell to Choir", 

00,0x1C8,	 " Pedal: 32' Contra Violone", 
59,0x1D3,	 " Pedal: 16' Principal", 
60,0x1D2,	 " Pedal: 16' Bourdon", 
61,0x1D1,	 " Pedal: 16' Lieblich Gedeckt", 
62,0x1D0,	 " Pedal: 16' Dulciana", 
63,0x1DF,	 " Pedal: 8' Octave", 
64,0x1DE,	 " Pedal: 8' Flute", 
65,	0,	 " Pedal: 8' Gemshorn", //	01/02/23	not	working
66,	0,	 " Pedal: 4' Choralbass", 
67,0x1DB,	 " Pedal: 16' Bombarde", 
68,0x1DA,	 " Pedal: 8' Trompette (sw)", 
69,0x1D9,	 " Pedal: 4' Clairon (sw)", 
30,0x1D8,	 " Pedal: 8' Great to Pedal", 
31,0x1E7,	 " Pedal: 4' Great to Pedal", 
32,0x1E6,	 " Pedal: 8' Swell to Pedal", 
33,0x1E5,	 " Pedal: 4' Swell to Pedal", 
34,0x1E4,	 " Pedal: 8' Choir to Pedal", 
35,0x1E3,	 " Pedal: 4' Choir to Pedal", 

38,0,	 " Tremulants Main Tremulant", 
37,0,	 " Tremulants Flute Tremulant-Light", 
36,0,	 " Tremulants Flute Tremulant-Full", 

12,0,	 " Great 16' Gemshorn", 
11,0,	 " Great 8' Principal", 
10,0,	 " Great 8' Bourdon", 
9,0,	 " Great 4' Octave", 
8,0,	 " Great 4' Spitz flote", 
7,0,	 " Great 2-2/3' Twelfth", 
6,0,	 " Great 2' Super Octave", 
5,0,	 " Great 2' Blockflote", 
4,0,	 " Great Mixture III", 
3,0,	 " Great 4' Great to Great", 
2,0,	 " Great 16' Swell to Great", 
1,0,	 " Great 8' Swell to Great", 
0,0,	 " Great 4' Swell to Great", 
56,0x1F0,	 " Great 16' Choir to Great", 
57,0x1F1,	 " Great 8' Choir to Great", 
58,0x1F2,	 " Great 4' Choir to Great", 
-1,-1,""};


void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  setupTabStopDriver();
  setupTabStopReader();

  for (int i = 0; i < 74; i++) {
    TabPulseOff(i, 100);
  }
}

void loop() {
  for (int i = 0;Pedal[i].I2C_BIT!=-1 && Pedal[i].SPIaddress!=-1; i++) {
    TabPulseOn(Pedal[i].SPIaddress, 100);

    int mux = 7;
    bool printed = false;
    for (int chip = 0; chip < 7; chip++) {
      for (int bit = 0; bit < 8; bit++) {
        int address = mux << 6 | chip << 3 | bit;
        // address=0x1c8;
        if (isTabSet(address) == 1) {
          printed = true;
          Serial.print(Pedal[i].SPIaddress);
          Serial.print(" 0x");
          Serial.print(address, HEX);
          Serial.print(" ");
          Serial.print(Pedal[i].TabStop);
          Serial.print(" ");
        }
      }
    }
    if (printed) {
      Serial.println();
      printed = false;
    }
    TabPulseOff(Pedal[i].SPIaddress, 100);
  }
}

