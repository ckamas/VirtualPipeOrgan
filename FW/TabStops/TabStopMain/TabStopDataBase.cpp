#include <cstddef>
#include "TabStopDataBase.h"

TabStops stops[]=
{
////////////////////////////
// top level of tab stops //
////////////////////////////

// typedef struct {
//  const int SPIaddress; // for setting the tabstop to a particular state
//  const int I2C_BIT; // for reading the tapstop's current state.
// // int MidiAddr; // for now we will AssUme that this is the same as the array index
// unsigned long timestamp;
// State MyState;
// const char *TabStop;
// } TabStops;

// SPIaddress, I2C_BIT, timestamp, MyState, *TabStop

13,0x1F3,false,0,standby,	 " Swell 8 foot Geigen Diapason", 
14,0x1F4,false,0,standby,	 " Swell 8' Rohr flote", 
15,0x1F5,false,0,standby,	 " Swell 8' Salicional", 
16,0x1F6,false,0,standby,	 " Swell 8' Voix Celeste", 
17,0x1F7,false,0,standby,	 " Swell 8' Flute Celests II", // need 60ms to move this one!
18,0x1E8,false,0,standby,	 " Swell 4' Prestant", 
19,0x1E9,false,0,standby,	 " Swell 4' Nacht horn", 
20,0x1EA,false,0,standby,	 " Swell 16' Fagotto", 
21,0x1EB,false,0,standby,	 " Swell 8' Trompette", 
22,0x1EC,false,0,standby,	 " Swell 8' Oboe", 
23,0x1ED,false,0,standby,	 " Swell 4' Clairon", 
24,0x1EE,false,0,standby,	 " Swell 16' Swell to Swell", 
25,0x1EF,false,0,standby,	 " Swell Swell Unison Off", 
26,0x1E0,false,0,standby,	 " Swell 4' Swell to Swell", 

27,0x1E1,false,0,standby,	 " Antiphonal Provisions Swell Main Off", 
28,0x1E2,false,0,standby,	 " Antiphonal Provisions Swell Antiphonal On", 
40,0x1D6,false,0,standby,	 " Antiphonal Provisions Great/Choir Main Off", 
39,0x1D5,false,0,standby,	 " Antiphonal Provisions Great/Choir Antiphonal On", 

43,0x1C7,false,0,standby,	 " Choir 8' Viola", 
44,0x1C6,false,0,standby,	 " Choir 8' Gedeckt", 
45,0x1C5,false,0,standby,	 " Choir 8' Quintade (w/chiff)", 
46,0x1C4,false,0,standby,	 " Choir 8' Dulciana", 
47,0x1C3,false,0,standby,	 " Choir 4' Principal", 
48,0x1C2,false,0,standby,	 " Choir 4' Koppelflote", 
49,0x1C1,false,0,standby,	 " Choir 4' Quintadena (w/chiff)", 
50,0x1C0,false,0,standby,	 " Choir 2-2/3' Nazard", 
51,0x1CF,false,0,standby,	 " Choir 2' Flachflote", 
52,0x1CE,false,0,standby,	 " Choir 1-3/5' Tierce", 
53,0x1CD,false,0,standby,	 " Choir 1' Sifflote", 
54,0x187,false,0,standby,  " Choir Harp",
55,0x186,false,0,standby,  " Choir Carillon", 

70,0x1CC,false,0,standby,	 " Choir 16' Choir to Choir", 
71,0x1CB,false,0,standby,	 " Choir Choir to Unison Off", 
72,0x1CA,false,0,standby,	 " Choir 4' Choir to Choir", 
73,0x1C9,false,0,standby,	 " Choir 16' Swell to Choir", 
42,0x1C8,false,0,standby,	 " Choir 8' Swell to Choir", 
41,0x1D7,false,0,standby,	 " Choir 4' Swell to Choir", 

///////////////////////////////
// bottom level of tab stops //
///////////////////////////////

29,0x1D4,false,0,standby,	 " Pedal: 32' Contra Violone", 
59,0x1D3,false,0,standby,	 " Pedal: 16' Principal", 
60,0x1D2,false,0,standby,	 " Pedal: 16' Bourdon", 
61,0x1D1,false,0,standby,	 " Pedal: 16' Lieblich Gedeckt", 
62,0x1D0,false,0,standby,	 " Pedal: 16' Dulciana", 
63,0x1DF,false,0,standby,	 " Pedal: 8' Octave", 
64,0x1DE,false,0,standby,	 " Pedal: 8' Flute", 

65,0x1DD,false,0,standby,	 " Pedal: 8' Gemshorn", //	01/02/23	not	working
66,0x1DC,false,0,standby,	 " Pedal: 4' Choralbass", 

67,0x1DB,false,0,standby,	 " Pedal: 16' Bombarde", 
68,0x1DA,false,0,standby,	 " Pedal: 8' Trompette (sw)", 
69,0x1D9,false,0,standby,	 " Pedal: 4' Clairon (sw)", 
30,0x1D8,false,0,standby,	 " Pedal: 8' Great to Pedal", 
31,0x1E7,false,0,standby,	 " Pedal: 4' Great to Pedal", 
32,0x1E6,false,0,standby,	 " Pedal: 8' Swell to Pedal", 
33,0x1E5,false,0,standby,	 " Pedal: 4' Swell to Pedal", 
34,0x1E4,false,0,standby,	 " Pedal: 8' Choir to Pedal", 
35,0x1E3,false,0,standby,	 " Pedal: 4' Choir to Pedal", 

38,0x18A,false,0,standby,	 " Tremulants Main Tremulant", 
37,0x189,false,0,standby,	 " Tremulants Flute Tremulant-Light", 
36,0x188,false,0,standby,	 " Tremulants Flute Tremulant-Full", 

12,0x18B,false,0,standby,	 " Great 16' Gemshorn", 
11,0x18C,false,0,standby,	 " Great 8' Principal", 
10,0x18D,false,0,standby,	 " Great 8' Bourdon", 
9,0x18E,false,0,standby,	 " Great 4' Octave", 
8,0x18F,false,0,standby,	 " Great 4' Spitz flote", 
7,0x1F8,false,0,standby,	 " Great 2-2/3' Twelfth", 
6,0x1F9,false,0,standby,	 " Great 2' Super Octave", 
5,0x1FA,false,0,standby,	 " Great 2' Blockflote", 
4,0x1FB,false,0,standby,	 " Great Mixture III", 
3,0x1FC,false,0,standby,	 " Great 4' Great to Great", 
2,0x1FD,false,0,standby,	 " Great 16' Swell to Great", 
1,0x1FE,false,0,standby,	 " Great 8' Swell to Great", 
0,0x1FF,false,0,standby,	 " Great 4' Swell to Great", 

56,0x1F0,false,0,standby,	 " Great 16' Choir to Great", 
57,0x1F1,false,0,standby,	 " Great 8' Choir to Great", 
58,0x1F2,false,0,standby,	 " Great 4' Choir to Great", 

-1,-1,false,0,standby,""};

const int stopsSize=sizeof(stops)/sizeof(stops[0]);
