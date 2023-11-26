void setupTabStopReader();
void scanTabs(void);
void scanTabsPrintCode(void);
int readPCF8574(uint8_t mux, uint8_t address);
int isTabSet(int tabAddress);  // bits 8,7,6 mux, bits 5,4,3 are the chip, bits 2,1,0 are the bit
