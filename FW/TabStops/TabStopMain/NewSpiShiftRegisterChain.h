#ifndef _SpiShiftRegisterChain_h
#define _SpiShiftRegisterChain_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SPI.h"

class NewSpiShiftRegisterChain {
public: // constructor/ destructor
	NewSpiShiftRegisterChain(unsigned int latchPin, unsigned int dataLengthBytes);
	~NewSpiShiftRegisterChain();

public: // functions
	void setBitOff(unsigned int bitNumber, bool writeData = true);
	void setBitOn(unsigned int bitNumber, bool writeData = true);
	void setDataToZeros();
	void toggleBit(unsigned int bitNumber, bool writeData = true);
	void writeData() const;

private: // functions
	void allocateMemory();
	void setPinModes() const;

private: // variables
	byte* _dataArray;
	unsigned int _dataLengthBytes;
	unsigned int _latchPin;
	SPISettings _spiSettings;
};


#endif
