#include "4002.h"

using namespace std;


Intel4002::Intel4002()
Intel4002::~Intel4002()

Intel4002::bool isRAMAdrAccessable(const ERAMBank bank, const ERAMChip chips) const
Intel4002::uint4_t readRAMNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress) const
Intel4002::bool writeRAMNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress, const uint4_t value)
Intel4002::bool isStatusAdrAccessable(const ERAMBank bank, const ERAMChip chip) const
Intel4002::uint4_t readStatusNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress) const
Intel4002::bool writeStatusNibble(const ERAMBank bank, const ERAMChip chip, const ERAMRegister ramregister, const int nibbleaddress, const uint4_t value)
Intel4002::uint4_t readFromPortBuffer(const ERAMBank bank, const ERAMChip chip) const
Intel4002::ERAMCommand nextCommand(Intel4004Base *ptr, const UCommand command);

