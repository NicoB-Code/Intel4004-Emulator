#ifndef _MYINTEL4001_H_
#define _MYINTEL4001_H_

#include <4001.h>
using namespace std;

class MyIntel4001 : public Intel4001 {
public:
    enum {
        ROM_CELLS_EACH_CHIP = 256,
        MAX_NUMBER_OF_ROM_CHIPS = 16
    };

    /**
     * Ctor um den ROM Speicher zu erzeugen
     * @param installed_banks Installierte Bänke (Default alle 16 Bänke)
     */
    MyIntel4001(const uint16_t installed_banks = 0xFFFF);
    /**
     * Destruktor räumt den Speicher auf
     */
    virtual ~MyIntel4001();
    /**
     * Setzt die internen Register zurück (Datenzellen auf 0x00, Ports auch auf 0)
     */
    virtual void reset();
    /**
     * Welche Bänke sind in diesem System verbaut
     * @return Bits der eingeschalteten Bänke
     */
    virtual uint16_t getEnabledBank() const;
    /**
     * Liest das Programm ein (Typ binär)
     * @param path Quelldatei
     */
    virtual void writeFromBinaryFile(const char * const path);
    /**
     * Liest das Programm ein (Typ Intel HEX)
     * @param path Quelldatei
     */
    virtual void writeFromIntelHexFile(const char * const path);
    /**
     * Liest das Programm ein (Typ Bytes)
     * @param data Datenquelle
     * @param count Anzahl Bytes die geschrieben werden
     * @return Anzahl
     */
    virtual int writeFrom(uint8_t *data, const int count);
    /**
     * Ist die lokale Adresse vorhanden (gibt es diese Adresse 12bit).
     * falls nicht wird false zurückgegeben
     * @param address Lineare Adresse ohne Bankangabe
     * @return <c>true</c> wenn addressierbar, sonst <c>false</c>
     */
    virtual bool isLinAdrAccessable(const uint16_t address) const;
    /**
     * Liest ein Byte aus dem Speicher
     * @param address Adresse im Speicher
     * @return Byte
     */
    virtual uint8_t read(const UBankedAddress address) const;
    /**
     * Setzt die Adresse für I/O-Aktivitäten
     * @param source Adresse des Ports
     */
    virtual void setSource(const uint8_t source);
    /**
     * Liest Nibble aus Portschnittstelle
     * @param value Wert
     */
    virtual uint4_t readFromPort() const;
    /**
     * Schreibe Nibble auf Portschnittstelle
     * @param value Wert
     */
    virtual void writeToPort(const uint4_t value);
protected:
    /**
     * Löschte alle Speicherbereiche die nicht installiert sind
     */
    virtual void clearROMWhoIsNotInstalled();

    /**
     * Aktivierte Bänke
     */
    const uint16_t installed_banks;
    /**
     * Auswahl des installierten Chips (auch nicht installierte Bänke)
     */
    uint8_t source;
    /**
     * ROM Inhalt (auch nicht installierte Bänke)
     */
    uint8_t *ROM;
    /**
     * Ist ROM installiert (linear)
     */
    bool *INSTALLEDROM;
    /**
     * Port Inhalt (auch nicht installierte Bänke)
     */
    uint4_t *PORTS;
    /**
     * Maximale Anzahl von ROM Speicherstellen die das System überhaupt haben kann
     */
    static const size_t ROM_MEMORY_SIZE;
};

#endif
