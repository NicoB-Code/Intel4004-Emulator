#ifndef _4002_h_
#define _4002_h_

#include "MCS4BaseClasses.h"
#include <iostream>
using namespace std;

/** Basisklasse Intel 4002 RAM.*/
class Intel4002 : public Intel4002Base {
public:
	Intel4002() { 
	}
	~Intel4002() {
	}
 void reset();
	bool isRAMAdrAccessable(const ERAMBank bank, const ERAMChip chips) const;
	uint4_t readRAMNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress) const;
	bool writeRAMNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress, const uint4_t value);
	bool isStatusAdrAccessable(const ERAMBank bank, const ERAMChip chip) const;
	uint4_t readStatusNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress) const;
	bool writeStatusNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress, const uint4_t value);
	uint4_t readFromPortBuffer(const ERAMBank bank, const ERAMChip chip) const;

#ifdef _RAM_SPLITOFF_
	 ERAMCommand nextCommand(Intel4004Base *ptr, const UCommand command)
#endif
};