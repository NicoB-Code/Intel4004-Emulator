#ifndef _4004_h_
#define _4004_h_

#include "MCS4BaseClasses.h"
#include "4001.h" // 4001-RAM
#include "4002.h" // 4002-RAM
#include "4004_stack.h"
#include <cstdint> // including global header files

using namespace std;

/** Basisklasse Intel 4004 Emulation */
class Intel4004 : public Intel4004Base {
public:

    enum {
        MAXIMUM_AMOUT_OF_REGISTERS = 16
    };

	Intel4004() {
	}
	~Intel4004() {
	}
	void reset();
	bool getCarry() const;
#ifdef _RAM_SPLITOFF_
	  void setCarry(const bool value);
#endif
	  uint4_t getAccumulator() const;
#ifdef _RAM_SPLITOFF_

	  void setAccumulator(const uint4_t value);
#endif
	  UBankedAddress getPC() const;
	  uint4_t getRegister(const ERegister reg);
	  uint8_t getRegisterPair(const ERegister reg);
	  Intel4001Base* getPtrToROM();
	  Intel4002Base* getPtrToRAM();
	  Intel4004StackBase* getPtrToStack();
	  uint64_t getTicks() const;
	  void resetTicks();
	  bool getTestPin() const;
	  void setTestPin(const bool value);
	  void nextCommand();

    private: 
        typedef enum : uint8_t {
            NOP = 0x00,
            JCN_0 = 0x10,
            JCN_1 = 0x11,
            JCN_2 = 0x12,
            JCN_3 = 0x13,
            JCN_4 = 0x14,
            JCN_5 = 0x15,
            JCN_6 = 0x16,
            JCN_7 = 0x17,
            JCN_8 = 0x18,
            JCN_9 = 0x19,
            JCN_10 = 0x1A,
            JCN_11 = 0x1B,
            JCN_12 = 0x1C,
            JCN_13 = 0x1D,
            JCN_14 = 0x1E,
            JCN_15 = 0x1F,
            FIM_0P = 0x20,
            SRC_0P = 0x21,
            FIM_1P = 0x22,
            SRC_1P = 0x23,
            FIM_2P = 0x24,
            SRC_2P = 0x25,
            FIM_3P = 0x26,
            SRC_3P = 0x27,
            FIM_4P = 0x28,
            SRC_4P = 0x29,
            FIM_5P = 0x2A,
            SRC_5P = 0x2B,
            FIM_6P = 0x2C,
            SRC_6P = 0x2D,
            FIM_7P = 0x2E,
            SRC_7P = 0x2F,
            FIN_0P = 0x30,
            JIN_0P = 0x31,
            FIN_0P = 0x32,
            JIN_0P = 0x33,
            FIN_0P = 0x34,
            JIN_0P = 0x35,
            FIN_0P = 0x36,
            JIN_0P = 0x37,
            FIN_0P = 0x38,
            JIN_0P = 0x39,
            FIN_0P = 0x3A,
            JIN_0P = 0x3B,
            FIN_0P = 0x3C,
            JIN_0P = 0x3D,
            FIN_0P = 0x3E,
            JIN_0P = 0x3F,
            JUN_0  = 0x40,
            JUN_1  = 0x41,
            JUN_2  = 0x42,
            JUN_3  = 0x43,
            JUN_4  = 0x44,
            JUN_5  = 0x45,
            JUN_6  = 0x46,
            JUN_7  = 0x47,
            JUN_8  = 0x48,
            JUN_9  = 0x49,
            JUN_10  = 0x4A,
            JUN_11  = 0x4B,
            JUN_12  = 0x4C,
            JUN_13  = 0x4D,
            JUN_14  = 0x4E,
            JUN_15  = 0x4F,
            JMS_0  = 0x50,
            JMS_1  = 0x51,
            JMS_2  = 0x52,
            JMS_3  = 0x53,
            JMS_4  = 0x54,
            JMS_5  = 0x55,
            JMS_6  = 0x56,
            JMS_7  = 0x57,
            JMS_8  = 0x58,
            JMS_9  = 0x59,
            JMS_10  = 0x5A,
            JMS_11  = 0x5B,
            JMS_12  = 0x5C,
            JMS_13  = 0x5D,
            JMS_14  = 0x5E,
            JMS_15  = 0x5F,
            INC_0  = 0x60,
            INC_1  = 0x61,
            INC_2  = 0x62,
            INC_3  = 0x63,
            INC_4  = 0x64,
            INC_5  = 0x65,
            INC_6  = 0x66,
            INC_7  = 0x67,
            INC_8  = 0x68,
            INC_9  = 0x69,
            INC_10  = 0x6A,
            INC_11  = 0x6B,
            INC_12  = 0x6C,
            INC_13  = 0x6D,
            INC_14  = 0x6E,
            INC_15  = 0x6F,
            ISZ_0  = 0x70,
            ISZ_1  = 0x71,
            ISZ_2  = 0x72,
            ISZ_3  = 0x73,
            ISZ_4  = 0x74,
            ISZ_5  = 0x75,
            ISZ_6  = 0x76,
            ISZ_7  = 0x77,
            ISZ_8  = 0x78,
            ISZ_9  = 0x79,
            ISZ_10  = 0x7A,
            ISZ_11  = 0x7B,
            ISZ_12  = 0x7C,
            ISZ_13  = 0x7D,
            ISZ_14  = 0x7E,
            ISZ_15  = 0x7F,
            ADD_0  = 0x80,
            ADD_1  = 0x81,
            ADD_2  = 0x82,
            ADD_3  = 0x83,
            ADD_4  = 0x84,
            ADD_5  = 0x85,
            ADD_6  = 0x86,
            ADD_7  = 0x87,
            ADD_8  = 0x88,
            ADD_9  = 0x89,
            ADD_10  = 0x8A,
            ADD_11  = 0x8B,
            ADD_12  = 0x8C,
            ADD_13  = 0x8D,
            ADD_14  = 0x8E,
            ADD_15  = 0x8F,
            SUB_0  = 0x90,
            SUB_1  = 0x91,
            SUB_2  = 0x92,
            SUB_3  = 0x93,
            SUB_4  = 0x94,
            SUB_5  = 0x95,
            SUB_6  = 0x96,
            SUB_7  = 0x97,
            SUB_8  = 0x98,
            SUB_9  = 0x99,
            SUB_10  = 0x9A,
            SUB_11  = 0x9B,
            SUB_12  = 0x9C,
            SUB_13  = 0x9D,
            SUB_14  = 0x9E,
            SUB_15  = 0x9F,
            LD_0  = 0xA0,
            LD_1  = 0xA1,
            LD_2  = 0xA2,
            LD_3  = 0xA03,
            LD_4  = 0xA4,
            LD_5  = 0xA5,
            LD_6  = 0xA6,
            LD_7  = 0xA7,
            LD_8  = 0xA8,
            LD_9  = 0xA9,
            LD_10  = 0xAA,
            LD_11  = 0xAB,
            LD_12  = 0xAC,
            LD_13  = 0xAD,
            LD_14  = 0xAE,
            LD_15  = 0xAF,
            XCH_0  = 0xB0,
            XCH_1  = 0xB1,
            XCH_2  = 0xB2,
            XCH_3  = 0xB3,
            XCH_4  = 0xB4,
            XCH_5  = 0xB5,
            XCH_6  = 0xB6,
            XCH_7  = 0xB7,
            XCH_8  = 0xB8,
            XCH_9  = 0xB9,
            XCH_10  = 0xBA,
            XCH_11  = 0xBB,
            XCH_12  = 0xBC,
            XCH_13  = 0xBD,
            XCH_14  = 0xBE,
            XCH_15  = 0xBF,
            BBL_0  = 0xC0,
            BBL_1  = 0xC1,
            BBL_2  = 0xC2,
            BBL_3  = 0xC3,
            BBL_4  = 0xC4,
            BBL_5  = 0xC5,
            BBL_6  = 0xC6,
            BBL_7  = 0xC7,
            BBL_8  = 0xC8,
            BBL_9  = 0xC9,
            BBL_10  = 0xCA,
            BBL_11  = 0xCB,
            BBL_12  = 0xCC,
            BBL_13  = 0xCD,
            BBL_14  = 0xCE,
            BBL_15  = 0xCF,
            LDM_0  = 0xD0,
            LDM_1  = 0xD1,
            LDM_2  = 0xD2,
            LDM_3  = 0xD3,
            LDM_4  = 0xD4,
            LDM_5  = 0xD5,
            LDM_6  = 0xD6,
            LDM_7  = 0xD7,
            LDM_8  = 0xD8,
            LDM_9  = 0xD9,
            LDM_10  = 0xDA,
            LDM_11  = 0xDB,
            LDM_12  = 0xDC,
            LDM_13  = 0xDD,
            LDM_14  = 0xDE,
            LDM_15  = 0xDF,
            WRM  = 0xE0,
            WMP  = 0xE1,
            WRR  = 0xE2,
            WPM  = 0xE3,
            WR0  = 0xE4,
            WR1  = 0xE5,
            WR2  = 0xE6,
            WR3  = 0xE7,
            SBM  = 0xE8,
            RDM  = 0xE9,
            RDR  = 0xEA,
            ADM  = 0xEB,
            RD0  = 0xEC,
            RD1  = 0xED,
            RD2  = 0xEE,
            RD3  = 0xEF,
            CLB  = 0xF0,
            CLC  = 0xF1,
            IAC  = 0xF2,
            CMC  = 0xF3,
            CMA  = 0xF4,
            RAL  = 0xF5,
            RAR  = 0xF6,
            TCC  = 0xF7,
            DAC  = 0xF8,
            TCS  = 0xF9,
            STC  = 0xFA,
            DAA  = 0xFB,
            KBP  = 0xFC,
            DCL = 0xFD

        } BEFEHL;
        
        bool carryFlag;
        bool testingPin;
        uint4_t accumulator;
        uint64_t ticks;
        UBankedAddress PC;
        uint4_t *registers;
        Intel4001 *ROM;
        Intel4002 *RAM;
        Intel4004Stack *stack;

        /   --------------------- One word instructions --------------------- /
        
        /**
         * No Operation
         */
        void NOP();

        /**
         * Loads Data into the Accumulator
         */
        void LDM(UCommand command);

        /**
         * Loads index of a register into the Accumulator
         */
        void LD(Ucommand command);

        /**
        * Swaps index of register and Accumulator         
        */
        void XCH(UCommand command);

        /**
         * Add index of register to Accumulator (with carry)
         */
        void ADD(UCommand command);

        /**
         * Subtract index of register from accumulator (with borrow)
         */
        void SUB(UCommand command);

        /**
         * Increment index of register
         */
        void INC(UCommand command)

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

        /   --------------------- Accumulator Instructions --------------------- /


         /   --------------------- Two word machine instructions --------------------- /
};
#endif




 