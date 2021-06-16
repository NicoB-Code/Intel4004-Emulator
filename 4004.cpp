#include "4004.h"

using namespace std;

Intel4004::Intel4004()
Intel4004::~Intel4004()

Intel4004::void reset()
Intel4004::bool getCarry() const
Intel4004::void setCarry(const bool value)
Intel4004::uint4_t getAccumulator() const
Intel4004::void setAccumulator(const uint4_t value)
Intel4004::UBankedAddress getPC() const
Intel4004::uint4_t getRegister(const ERegister reg)
Intel4004::uint8_t getRegisterPair(const ERegister reg)
Intel4004::Intel4001Base* getPtrToROM()
Intel4004::Intel4002Base* getPtrToRAM()
Intel4004::Intel4004StackBase* getPtrToStack()
Intel4004::uint64_t getTicks() const
Intel4004::void resetTicks()
Intel4004::bool getTestPin() const
Intel4004::void setTestPin(const bool value)
Intel4004::void nextCommand()

Intel4004:: void NOP()
{
    ticks++;
}

Intel4004:: void LDM(UCommand command)
{
    uint4_t value = command.nibble.opa;
    accumulator = 0; // clear Accumulator
    accumulator = value;
    ticks++;
}

Intel4004::void LD(Ucommand command);
{
    uint4_t registerNumber = command.nibble.opa;
    accumulator = 0; // clear Accumulator
    accumulator = registers[registerNumber];
    ticks++;
}
Intel4004::void XCH(UCommand command){
    uint4_t registerNumber = command.nibble.opa;
    uint4_t change = accumulator;
    accumulator = registers[registerNumber];
    register[registerNumber] = change;
    ticks++;
}
Intel4004::void ADD(UCommand command)
{
    uint4_t registerNumber = command.nibble.opa;
    accumulator = accumulator + registers[registerNumber] + carryFlag; // Add Accumulator
    carryFlag = accumulator >> 4;
    accumulator &= ~(0b11110000);  // clear bits 4-7
    ticks++; 
}
Intel4004::void SUB(UCommand command)
Intel4004::void INC(UCommand command)
Intel4004::void BBL(UCommand command)
Intel4004::void JIN(UCommand command)
Intel4004::void SRC(UCommand command)
Intel4004::void FIN(UCommand command)
