#include "NewSpiShiftRegisterChain.h"
#include <SPI.h>

#define numBoards 20
NewSpiShiftRegisterChain my595(10, numBoards);


typedef struct {
//  char keyboard[20];
//  char name[20]; 
  int address;
//  int MidiAddr;
} keyBoard;


keyBoard Pedal[]=
{
  59, 
  #if 0
    /*Swell 8' Geigen Diapason*/	13,
    /*Swell 8' Rohr flote*/	14,
    /*Swell 8' Salicional*/	15,
    /*Swell 8' Voix Celeste*/	16,
    /*Swell 8' Flute Celests II*/	17,
    /*Swell 4' Prestant*/	18,
    /*Swell 4' Nacht horn*/	19,
    /*Swell 16' Fagotto*/	20,
    /*Swell 8' Trompette*/	21,
    /*Swell 8' Oboe*/	22,
    /*Swell 4' Clairon*/	23,
    /*Swell 16' Swell to Swell*/	24,
    /*Swell Swell Unison Off*/	25,
    /*Swell 4' Swell to Swell*/	26,

    /*Antiphonal Provisions Swell Main Off*/	27,
    /*Antiphonal Provisions Swell Antiphonal On*/	28,
    /*Antiphonal Provisions Great/Choir Main Off*/	40,
    /*Antiphonal Provisions Great/Choir Antiphonal On*/	39,

    /*Antiphonal Provisions ?*/	29,

    /*Choir 8' Viola*/	43,
    /*Choir 8' Gedeckt*/	44,
    /*Choir 8' Quintade (w/chiff)*/	45,
    /*Choir 8' Dulciana*/	46,
    /*Choir 4' Principal*/	47,
    /*Choir 4' Koppelflote*/	48,
    /*Choir 4' Quintadena (w/chiff)*/	49,
    /*Choir 2-2/3' Nazard*/	50,
    /*Choir 2' Flachflote*/	51,
    /*Choir 1-3/5' Tierce*/	52,
    /*Choir 1' Sifflote*/	53,
    /*Choir Harp*/	54,
    /*Choir Carillon*/	55,
    /*Choir 16' Choir to Choir*/	70,
    /*Choir Choir to Unison Off*/	71,
    /*Choir 4' Choir to Choir*/	72,
    /*Choir 16' Swell to Choir*/	73,
    /*Choir 8' Swell to Choir*/	42,
    /*Choir 4' Swell to Choir*/	41,

    /*Pedal: 32' Contra Violone*/ -1,
    /*Pedal: 16' Principal*/	59,
    /*Pedal: 16' Bourdon*/	60,
    /*Pedal: 16' Lieblich Gedeckt*/	61,
    /*Pedal: 16' Dulciana*/	62,
    /*Pedal: 8' Octave*/	63,
    /*Pedal: 8' Flute*/	64,
    /*Pedal: 8' Gemshorn*/	65, // 1/2 not working
    /*Pedal: 4' Choralbass*/	66,
    /*Pedal: 16' Bombarde*/	67,
    /*Pedal: 8' Trompette (sw)*/	68,
    /*Pedal: 4' Clairon (sw)*/	69,
    /*Pedal: 8' Great to Pedal*/	30,
    /*Pedal: 4' Great to Pedal*/	31,
    /*Pedal: 8' Swell to Pedal*/	32,
    /*Pedal: 4' Swell to Pedal*/	33,
    /*Pedal: 8' Choir to Pedal*/	34,
    /*Pedal: 4' Choir to Pedal*/	35,

    /*Tremulants Main Tremulant*/	38,
    /*Tremulants Flute Tremulant-Light*/	37,
    /*Tremulants Flute Tremulant-Full*/	36,

    /*Great 16' Gemshorn*/	12,
    /*Great 8' Principal*/	11,
    /*Great 8' Bourdon*/	10,
    /*Great 4' Octave*/	9,
    /*Great 4' Spitz flote*/	8,
    /*Great 2-2/3' Twelfth*/	7,
    /*Great 2' Super Octave*/	6,
    /*Great 2' Blockflote*/	5,
    /*Great Mixture III*/	4,
    /*Great 4' Great to Great*/	3,
    /*Great 16' Swell to Great*/	2,
    /*Great 8' Swell to Great*/	1,
    /*Great 4' Swell to Great*/	0,
    /*Great 16' Choir to Great*/	56,
    /*Great 8' Choir to Great*/	57,
    /*Great 4' Choir to Great*/	58,
    #endif

    /* */	-999999,
};

void printDB()
{
  int i=0;
  while (Pedal[i].address>=-99)
  {
    Serial.print("Address=");
    Serial.println(Pedal[i].address);
    i++;
  }
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  SPI.begin();
  my595.setDataToZeros();
  my595.writeData();
  printDB();
}

void on (NewSpiShiftRegisterChain* my595, unsigned int bit)
{
  unsigned int board=bit>>3;
  unsigned int pin=bit&0x7;
  return my595->setBitOn((board<<3)+(7-pin));
}

void off (NewSpiShiftRegisterChain* my595, unsigned int bit)
{
  unsigned int board=bit>>3;
  unsigned int pin=bit&0x7;
  return my595->setBitOff((board<<3)+(7-pin));
}

void toggle (int tab)
{
  const int TABA = 0;
  const int TABB = 1;
  const int DELAY=250;

  int i=tab*2;

  // turn on a and off b
  on(&my595,TABA + i);
  off(&my595,TABB + i);
  delay(DELAY);

  // turn off a
  off(&my595,TABA + i);
  delay(DELAY/2);
  
  // turn on b and off a
  on(&my595, TABB + i);
  off(&my595, TABA + i);
  delay(DELAY);
  
  // turn off b
  off(&my595, TABB + i);
  delay(DELAY/2);
}

void offDelay (NewSpiShiftRegisterChain* sr, int tab, int pause)
{
  const int TABA = 0;
  const int TABB = 1;

  int i=tab*2;

  // turn on a and off b
  on(sr,TABA + i);
  off(sr,TABB + i);
  delay(pause);

  // turn off a
  off(sr,TABA + i);
}

void onDelay (NewSpiShiftRegisterChain* sr, int tab, int pause)
{
  const int TABA = 0;
  const int TABB = 1;

  int i=tab*2;

  // turn on b and off a
  on(sr, TABB + i);
  off(sr, TABA + i);
  delay(pause);
  
  // turn off b
  off(sr, TABB + i);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i=0;
  while (Pedal[i].address>=-99)
  {
    Serial.print("Turning (");
    Serial.print(i);
    Serial.print(") on @ Address=");
    Serial.println(Pedal[i].address);

    onDelay (&my595,Pedal[i].address,100);
    i++;
  }
  delay(1000);

  i=0;
  while (Pedal[i].address>=-99)
  {
    Serial.print("Turning (");
    Serial.print(i);
    Serial.print(") off @ Address=");
    Serial.println(Pedal[i].address);

    offDelay (&my595,Pedal[i].address,100);
    i++;
  }

  delay(1000);

}