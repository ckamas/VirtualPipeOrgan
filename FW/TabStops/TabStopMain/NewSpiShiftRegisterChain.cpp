#include "NewSpiShiftRegisterChain.h"


// 
// public constructor/ destructor
// 
NewSpiShiftRegisterChain::NewSpiShiftRegisterChain(unsigned int latchPin, unsigned int dataLengthBytes) :
	_dataArray(0),
	_dataLengthBytes(dataLengthBytes),
	_latchPin(latchPin),
	_spiSettings(4000000, LSBFIRST, SPI_MODE0)
{
	setPinModes();
	allocateMemory();
	setDataToZeros();
}

NewSpiShiftRegisterChain::~NewSpiShiftRegisterChain() {
	if(_dataArray)
		delete[] _dataArray;
}


//
// public functions
//
void NewSpiShiftRegisterChain::setBitOff(unsigned int bitNumber, bool writeData/*= true*/){
	_dataArray[bitNumber / 8] &= ~(0b10000000 >> (bitNumber % 8));
	if (writeData)
		this->writeData();
}

void NewSpiShiftRegisterChain::setBitOn(unsigned int bitNumber, bool writeData/*= true*/) {
	_dataArray[bitNumber / 8] |= 0b10000000 >> (bitNumber % 8);
	if (writeData)
		this->writeData();
}

void NewSpiShiftRegisterChain::setDataToZeros() {
	for (unsigned int i = 0; i < _dataLengthBytes; i++)
		_dataArray[i] = 0b00000000;
}

void NewSpiShiftRegisterChain::toggleBit(unsigned int bitNumber, bool writeData/*= true*/) {
	_dataArray[bitNumber / 8] ^= 0b10000000 >> (bitNumber % 8);
	if (writeData)
		this->writeData();
}

void NewSpiShiftRegisterChain::writeData() const {
	SPI.beginTransaction(_spiSettings);
	digitalWrite(_latchPin, LOW);

	for (int i = _dataLengthBytes - 1; i >= 0; i--)
		SPI.transfer(_dataArray[i]);

	digitalWrite(_latchPin, HIGH);
	SPI.endTransaction();
}


//
// private functions
//
void NewSpiShiftRegisterChain::allocateMemory() {
	if (_dataArray)
		delete[] _dataArray;

	_dataArray = new byte[_dataLengthBytes];
}

void NewSpiShiftRegisterChain::setPinModes() const {
	pinMode(_latchPin, OUTPUT);
}
