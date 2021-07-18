#ifndef _4004_h_
#define _4004_h_
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // local header
	#include "MCS4BaseClasses.h"
	#include "4001.h"
	#include "4002.h"
#elif __unix__
	#include "../inc/MCS4BaseClasses.h"
	#include "4001.h"
	#include "4002.h"
#endif
#include "4004_stack.h"
#include <cstdint> // global header
using namespace std; // namespace

class Intel4004 : public Intel4004Base {
public:
	enum {
        MAX_NUMBER_OF_REGISTERS = 16,
		TICKS_PER_CYCLE = 8
    };
	/**
	 * Konstruktor
	 */
	Intel4004(const uint16_t installed_ROM_Chips = 0xFFFF, const uint32_t installed_RAM_Chips = 0xFFFFFFFF);
	/**
	 * Destruktor
	 */
	virtual ~Intel4004();
	/**
	 * Setzt den Prozessor zurück
	 */
	virtual void reset();
	/**
	 * Gibt den Wert des Übertrags aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Übertrag
	 */
	virtual bool getCarry() const;
	/**
	 * Gibt den Wert des Akkumulators aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Akkumulator
	 */
	virtual uint4_t getAccumulator() const;
	/**
	 * Gibt die aktuelle Adresse der Ablaufsteuerung aus.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19
	 * @return Adresse der Ablaufsteuerung
	 */
	virtual UBankedAddress getPC() const;
	/**
	 * Dient zum auslesen eines Registers (Register 0..15).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19 und MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 11
	 * @param reg Registernummer
	 * @return Nibble
	 */
	virtual uint4_t getRegister(const ERegister reg);
	/**
	 * Dient zum auslesen eines Registerspaars (Register R1R0 ... R15R14).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.19 und MCS-4_Assembly_Language_Programming_Manual_Dec73.pdf S. 11
	 * @param reg Registerpaar Nummer
	 * @return Byte
	 */
	virtual uint8_t getRegisterPair(const ERegister reg);
	/**
	 * Gibt den ROM Handle zurück.
	 * @return ROM Handle
	 */
	virtual Intel4001Base* getPtrToROM();
	/**
	 * Gibt den RAM Handle zurück.
	 * @return RAM Handle
	 */
	virtual Intel4002Base* getPtrToRAM();
	/**
	 * Gibt den Stack Handle zurück.
	 * @return Stack Handle
	 */
	virtual Intel4004StackBase* getPtrToStack();
	/**
	 * Gibt die Anzahl der Ticks (Subzyklen) zurück die bisher gemessen wurden.
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @return Anzahl Ticks
	 */
	virtual uint64_t getTicks() const;
	/**
	 * Setzt die Ticks zurück (Subzyklen)
	 */
	virtual void resetTicks();
	/** Gibt den Pin zurück (Hardwareschnittstelle).
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @return <c>true</c> wenn eingeschaltet, sonst <c>false</c>
	 */
	virtual bool getTestPin() const;
	/**
	 * Setzt den Pin (Hardwareschnittstelle)
	 * <br>Hinweis:</br> Siehe studienarbeit-4004.pdf S.6
	 * @param value <c>true</c> wenn eingeschaltet, sonst <c>false</c>
	 */
	virtual void setTestPin(const bool value);
	/** Ruft die Programmablaufschnittstelle auf. Über diese Schnittstelle können die Befehle Step für Step abgearbeitet werden. */
	virtual void nextCommand();

private:
	bool carryFlag;
	bool testPin;
	uint4_t accumulator;
	uint64_t ticks;
	UBankedAddress PC;
	uint4_t *registers;
	Intel4001 *ROM;
	Intel4002 *RAM;
	Intel4004Stack *stack;

	//   --------------------- One word instructions --------------------- /
	/**
	 * No Operation
	 */
	void NOP();
	/**
	 * Load data to Accumulator
	 */
	void LDM(UCommand command);
	/**
	 * Load index register to Accumulator
	 */ 
	void LD(UCommand command);
	/**
	 * Exchange index register and accumulator
	 */ 
	void XCH(UCommand command);
	/**
	 * Add index register to accumulator with carry
	 */ 
	void ADD(UCommand command);
	/**
	 * Subtract index register from accumulator with borrow
	 */ 
	void SUB(UCommand command);
	/**
	 * Increment index register
	 */ 
	void INC(UCommand command);
	/**
	 * Branch back and load data to the accumulator
	 */ 
	void BBL(UCommand command);
	/**
	 * Jump indirect
	 */ 
	void JIN(UCommand command);
	/**
	 * Send register control
	 */ 
	void SRC(UCommand command);
	/**
	 * Fetch indirect from ROM
	 */ 
	void FIN(UCommand command);

	//   --------------------- Accumulator Instructions --------------------- /

	/**
	 * Clear both
	 */
	void CLB();
	/**
	 * Clear carry
	 */
	void CLC();
	/**
	 * Complement carry
	 */
	void CMC();
	/**
	 * Set carry
	 */
	void STC();
	/**
	 * Complement Accumulator
	 */
	void CMA();
	/**
	 * Increment accumulator
	 */
	void IAC();
	/**
	 * Decrement accumulator
	 */
	void DAC();
	/**
	 * Rotate left
	 */
	void RAL();
	/**
	 * Rotate right
	 */
	void RAR();
	/**
	 * Transmit carry and clear
	 */
	void TCC();
	/**
	 * Decimal adjust accumulator
	 */
	void DAA();
	/**
	 * Transfer carry subtract
	 */
	void TCS();
	/**
	 * Keyboard process
	 */
	void KBP();
	/**
	 * Designate command line
	 */
	void DCL();


	/**
	 * Jump unconditional
	 */
	void JUN(UCommand byte1, UCommand byte2);
	/**
	 * Jump to Subroutine
	 */
	void JMS(UCommand byte1, UCommand byte2);
	/**
	 * Jump conditional
	 */
	void JCN(UCommand byte1, UCommand byte2);
	/**
	 * Increment index register skip if zero
	 */
	void ISZ(UCommand byte1, UCommand byte2);
	/**
	 * Fetched immediate from ROM
	 */
	void FIM(UCommand byte1, UCommand byte2);



	/**
	 * Read RAM character
	 */
	void RDM();
	/**
	 * Read RAM status character 0-3
	 */
	void RDn(UCommand command);
	/**
	 * Read ROM port
	 */
	void RDR();
	/**
	 * Write accumulator into RAM character
	 */
	void WRM();
	/**
	 * Write accumulator into RAM status character 0-3
	 */
	void WRn(UCommand command);
	/**
	 * Write Program RAM
	 */
	void WPM();
	/**
	 * Write ROM port
	 */
	void WRR();
	/**
	 * Write memory port
	 */
	void WMP();
	/**
	 * Add from memory with carry
	 */
	void ADM();
	/**
	 * Subtract from memory with borrow
	 */
	void SBM();

};
#endif
