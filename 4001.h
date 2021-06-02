#ifndef _4001_h_
#define _4001_h_

#include<cstdint>
using namespace std;

typedef uint8_t uint4_t;
typedef uint16_t uint12_t;

/**
 * Bänke der Speicherverwaltung
 */
typedef enum : uint4_t {
    BANK0, //!< Bank 0
    BANK1, //!< Bank 1
    BANK2, //!< Bank 2
    BANK3, //!< Bank 3
    BANK4, //!< Bank 4
    BANK5, //!< Bank 5
    BANK6, //!< Bank 6
    BANK7, //!< Bank 7
    BANK8, //!< Bank 8
    BANK9, //!< Bank 9
    BANK10, //!< Bank 10
    BANK11, //!< Bank 11
    BANK12, //!< Bank 12
    BANK13, //!< Bank 13
    BANK14, //!< Bank 14
    BANK15 //!< Bank 15
} ERamBank;

/**
 * Adressangabe
 */
union UBankedAddress {
    /**
     * Initalisierungs-Konstruktor
     * @param value Linearer Speicherwert ohne Bankangabe
     */
    UBankedAddress(const uint12_t value = 0) :
        raw { value } {
    }

    /**
     * Initalisierungs-Konstruktor
     * @param bank Bankangabe
     * @param address Address segmentiert
     */
    UBankedAddress(const uint4_t bank, const uint8_t address) :
        banked { .address = address, .bank = bank } {
    }

    uint12_t raw;	//!< Rohwert

    struct {
        uint8_t address;	//!< Adresse im Segment
        uint8_t bank :4;	//!< Bankangabe
        uint8_t :4;
    } banked;	//!< Segmente in Bank und Segmentadresse

    /**
     * Erhöht die Adresse (Wert) um 1
     * @return Adresse (Wert) um 1 erhöht
     */
    uint12_t inc() {
        return raw = 0x0FFF & (raw + 1);
    }
};

/**
 * Array von ROM Bausteine abstrahiert auf das urpsrüngliche Speicherkonzept
 */
class Intel4001 {
public:
    /**
     * Ctor um den ROM Speicher zu erzeugen
     * @param installed_banks Installierte Bänke (Default alle 16 Bänke)
     */
    Intel4001(const uint16_t installed_banks = 0xFFFF) {}
    /**
     * Destruktor räumt den Speicher auf
     */
    virtual ~Intel4001() {}
    /**
     * Setzt die internen Register zurück (Datenzellen auf 0x00, Ports auch auf 0)
     */
    virtual void reset() = 0;
    /**
     * Welche Bänke sind in diesem System verbaut
     * @return Bits der eingeschalteten Bänke
     */
    virtual uint16_t getEnabledBank() const = 0;
    /**
     * Liest das Programm ein (Typ binär)
     * @param path Quelldatei
     */
    virtual void writeFromBinaryFile(const char * const path) = 0;
    /**
     * Liest das Programm ein (Typ Intel HEX)
     * @param path Quelldatei
     */
    virtual void writeFromIntelHexFile(const char * const path) = 0;
    /**
     * Liest das Programm ein (Typ Bytes)
     * @param data Datenquelle
     * @param count Anzahl Bytes die geschrieben werden
     * @return Anzahl
     */
    virtual int writeFrom(uint8_t *data, const int count) = 0;
    /**
     * Ist die lokale Adresse vorhanden (gibt es diese Adresse 12bit).
     * falls nicht wird false zurückgegeben
     * @param address Lineare Adresse ohne Bankangabe
     * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
     */
    virtual bool isLinAdrAccessable(const uint16_t address) const = 0;
    /**
     * Liest ein Byte aus dem Speicher
     * @param address Adresse im Speicher
     * @return Byte
     */
    virtual uint8_t read(const UBankedAddress address) const = 0;
    /**
     * Setzt die Adresse für I/O-Aktivitäten
     * @param source Adresse des Ports
     */
    virtual void setSource(const uint8_t source) = 0;
    /**
     * Liest Nibble aus Portschnittstelle
     * @param value Wert
     */
    virtual uint4_t readFromPort() const = 0;
    /**
     * Schreibe Nibble auf Portschnittstelle
     * @param value Wert
     */
    virtual void writeToPort(const uint4_t value) = 0;
};

#endif
