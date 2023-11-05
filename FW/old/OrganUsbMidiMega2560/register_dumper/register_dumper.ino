#include <Arduino.h>
#include <MCP23017.h>

MCP23017 A = MCP23017(0x20);
MCP23017 B = MCP23017(0x21);
MCP23017 C = MCP23017(0x22);
MCP23017 D = MCP23017(0x24);


void setup() {
  Serial.begin(115200);
  
  A.init();
  B.init();
  C.init();
  D.init();

  A.portMode(MCP23017Port::A,0xff,0xff,0xff);
  A.portMode(MCP23017Port::B,0xff,0xff,0xff);
  B.portMode(MCP23017Port::A,0xff,0xff,0xff);
  B.portMode(MCP23017Port::B,0xff,0xff,0xff);
  C.portMode(MCP23017Port::A,0xff,0xff,0xff);
  C.portMode(MCP23017Port::B,0xff,0xff,0xff);
  D.portMode(MCP23017Port::A,0xff,0xff,0xff);
  D.portMode(MCP23017Port::B,0xff,0xff,0xff);


}

void loop() {
  // put your main code here, to run repeatedly:
  uint64_t keys;

  keys=A.read();
  keys=keys<<16;
  keys|=B.read();
  keys=keys<<16;
  keys|=C.read();
  keys=keys<<16;
  keys|=D.read();
  
  Serial.println (keys,16);

}
