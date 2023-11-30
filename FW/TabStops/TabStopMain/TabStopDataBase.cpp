#include <cstddef>
#include "TabStopDataBase.h"

TabStops stops[]=
{
////////////////////////////
// top level of tab stops //
////////////////////////////


// typedef struct {
//   // for the tab stop solenoids
//   const int SPIaddress;           // for driving the tabstop to a particular state
//   State MyState;                  // driving state
//   unsigned long DriveTimeStamp;   // how long to leave the solenoid energized
  
//   // for reading the state of the tabstops
//   const int I2C_BIT;              // for reading the tapstop's current state.
//   bool tabReadSet;                // current state driven out on midi
//   unsigned long ReadTimeStamp;    // when to start reading the i2c again

//   const char *TabStop;            // human readable name
// } TabStops;


13,standby,0,0x1F3,false,0,"Swell 8 foot Geigen Diapason",
14,standby,0,0x1F4,false,0,"Swell 8' Rohr flote",
15,standby,0,0x1F5,false,0,"Swell 8' Salicional",
16,standby,0,0x1F6,false,0,"Swell 8' Voix Celeste",
17,standby,0,0x1F7,false,0,"Swell 8' Flute Celests II", // need 60ms to move this one!
18,standby,0,0x1E8,false,0,"Swell 4' Prestant",
19,standby,0,0x1E9,false,0,"Swell 4' Nacht horn",
20,standby,0,0x1EA,false,0,"Swell 16' Fagotto",
21,standby,0,0x1EB,false,0,"Swell 8' Trompette",
22,standby,0,0x1EC,false,0,"Swell 8' Oboe",
23,standby,0,0x1ED,false,0,"Swell 4' Clairon",
24,standby,0,0x1EE,false,0,"Swell 16' Swell to Swell",
25,standby,0,0x1EF,false,0,"Swell Swell Unison Off",
26,standby,0,0x1E0,false,0,"Swell 4' Swell to Swell",

27,standby,0,0x1E1,false,0,"Antiphonal Provisions Swell Main Off",
28,standby,0,0x1E2,false,0,"Antiphonal Provisions Swell Antiphonal On",
40,standby,0,0x1D6,false,0,"Antiphonal Provisions Great/Choir Main Off",
39,standby,0,0x1D5,false,0,"Antiphonal Provisions Great/Choir Antiphonal On",

43,standby,0,0x1C7,false,0,"Choir 8' Viola",
44,standby,0,0x1C6,false,0,"Choir 8' Gedeckt",
45,standby,0,0x1C5,false,0,"Choir 8' Quintade (w/chiff)",
46,standby,0,0x1C4,false,0,"Choir 8' Dulciana",
47,standby,0,0x1C3,false,0,"Choir 4' Principal",
48,standby,0,0x1C2,false,0,"Choir 4' Koppelflote",
49,standby,0,0x1C1,false,0,"Choir 4' Quintadena (w/chiff)",
50,standby,0,0x1C0,false,0,"Choir 2-2/3' Nazard",
51,standby,0,0x1CF,false,0,"Choir 2' Flachflote",
52,standby,0,0x1CE,false,0,"Choir 1-3/5' Tierce",
53,standby,0,0x1CD,false,0,"Choir 1' Sifflote",
54,standby,0,0x187,false,0,"Choir Harp",
55,standby,0,0x186,false,0,"Choir Carillon",

70,standby,0,0x1CC,false,0,"Choir 16' Choir to Choir",
71,standby,0,0x1CB,false,0,"Choir Choir to Unison Off",
72,standby,0,0x1CA,false,0,"Choir 4' Choir to Choir",
73,standby,0,0x1C9,false,0,"Choir 16' Swell to Choir",
42,standby,0,0x1C8,false,0,"Choir 8' Swell to Choir",
41,standby,0,0x1D7,false,0,"Choir 4' Swell to Choir",

///////////////////////////////,,,,,,,
// bottom level of tab stops //,,,,,,,
///////////////////////////////,,,,,,,

29,standby,0,0x1D4,false,0,"Pedal: 32' Contra Violone",
59,standby,0,0x1D3,false,0,"Pedal: 16' Principal",
60,standby,0,0x1D2,false,0,"Pedal: 16' Bourdon",
61,standby,0,0x1D1,false,0,"Pedal: 16' Lieblich Gedeckt",
62,standby,0,0x1D0,false,0,"Pedal: 16' Dulciana",
63,standby,0,0x1DF,false,0,"Pedal: 8' Octave",
64,standby,0,0x1DE,false,0,"Pedal: 8' Flute",

65,standby,0,0x1DD,false,0,"Pedal: 8' Gemshorn", //	01/02/23	not	working
66,standby,0,0x1DC,false,0,"Pedal: 4' Choralbass",

67,standby,0,0x1DB,false,0,"Pedal: 16' Bombarde",
68,standby,0,0x1DA,false,0,"Pedal: 8' Trompette (sw)",
69,standby,0,0x1D9,false,0,"Pedal: 4' Clairon (sw)",
30,standby,0,0x1D8,false,0,"Pedal: 8' Great to Pedal",
31,standby,0,0x1E7,false,0,"Pedal: 4' Great to Pedal",
32,standby,0,0x1E6,false,0,"Pedal: 8' Swell to Pedal",
33,standby,0,0x1E5,false,0,"Pedal: 4' Swell to Pedal",
34,standby,0,0x1E4,false,0,"Pedal: 8' Choir to Pedal",
35,standby,0,0x1E3,false,0,"Pedal: 4' Choir to Pedal",

38,standby,0,0x18A,false,0,"Tremulants Main Tremulant",
37,standby,0,0x189,false,0,"Tremulants Flute Tremulant-Light",
36,standby,0,0x188,false,0,"Tremulants Flute Tremulant-Full",

12,standby,0,0x18B,false,0,"Great 16' Gemshorn",
11,standby,0,0x18C,false,0,"Great 8' Principal",
10,standby,0,0x18D,false,0,"Great 8' Bourdon",
9,standby,0,0x18E,false,0,"Great 4' Octave",
8,standby,0,0x18F,false,0,"Great 4' Spitz flote",
7,standby,0,0x1F8,false,0,"Great 2-2/3' Twelfth",
6,standby,0,0x1F9,false,0,"Great 2' Super Octave",
5,standby,0,0x1FA,false,0,"Great 2' Blockflote",
4,standby,0,0x1FB,false,0,"Great Mixture III",
3,standby,0,0x1FC,false,0,"Great 4' Great to Great",
2,standby,0,0x1FD,false,0,"Great 16' Swell to Great",
1,standby,0,0x1FE,false,0,"Great 8' Swell to Great",
0,standby,0,0x1FF,false,0,"Great 4' Swell to Great",

56,standby,0,0x1F0,false,0,"Great 16' Choir to Great",
57,standby,0,0x1F1,false,0,"Great 8' Choir to Great",
58,standby,0,0x1F2,false,0,"Great 4' Choir to Great",
//   const int SPIaddress;           // for driving the tabstop to a particular state
//   State MyState;                  // driving state
//   unsigned long DriveTimeStamp;   // how long to leave the solenoid energized
  
//   // for reading the state of the tabstops
//   const int I2C_BIT;              // for reading the tapstop's current state.
//   bool tabReadSet;                // current state driven out on midi
//   unsigned long ReadTimeStamp;    // when to start reading the i2c again

//   const char *TabStop;            // human readable name


-1,standby,0,-1,false,0,""};

const int stopsSize=sizeof(stops)/sizeof(stops[0]);
