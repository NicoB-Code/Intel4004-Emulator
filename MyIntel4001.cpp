extern "C" {
#include <intelhex.h>
}

#include <MyIntel4001.h>
#include <cstring>
#include <fstream>
using namespace std;

MyIntel4001::MyIntel4001(const uint16_t installed_banks) :
    installed_banks(installed_banks), source(0), ROM(nullptr), INSTALLEDROM(nullptr), PORTS(nullptr) {

    ROM = new uint8_t[ROM_MEMORY_SIZE];
    INSTALLEDROM = new bool[MAX_NUMBER_OF_ROM_CHIPS];
    PORTS = new uint4_t[MAX_NUMBER_OF_ROM_CHIPS];

    //ROM Bereiche die vorhanden sind instalieren
    {
        uint16_t banks = {installed_banks};
        for(auto chip = 0; chip < MAX_NUMBER_OF_ROM_CHIPS; ++chip, banks >>= 1)
            INSTALLEDROM[chip] = banks & 1;
    }
}

MyIntel4001::~MyIntel4001() {
    delete [] ROM;
    delete [] INSTALLEDROM;
    delete [] PORTS;
}


void MyIntel4001::reset() {

    memset(ROM, 0, ROM_MEMORY_SIZE);
    memset(PORTS, 0, MAX_NUMBER_OF_ROM_CHIPS);
    source = 0;
}

uint16_t MyIntel4001::getEnabledBank() const {
    return 0;
}

void MyIntel4001::writeFromBinaryFile(const char * const path) {
    ifstream is (path, ifstream::binary);
    if(is.is_open()) {
        is.read((char *)ROM,ROM_MEMORY_SIZE);

        clearROMWhoIsNotInstalled();

        is.close();
    }
}

void MyIntel4001::writeFromIntelHexFile(const char * const path) {
    if(!readFile(path, ROM, ROM_MEMORY_SIZE, nullptr))
    {
        //irgend eine Fehlerabarbeitung;
    }
    else clearROMWhoIsNotInstalled();
}

int MyIntel4001::writeFrom(uint8_t *data, const int count) {
    if ((count < 1) || (count > static_cast<const int>(ROM_MEMORY_SIZE)))
        return 0;
    else {
        memcpy(ROM, data, count);

        clearROMWhoIsNotInstalled();

        return count;
    }
}

bool MyIntel4001::isLinAdrAccessable(const uint16_t address) const {
    UBankedAddress banked = {address};
    return INSTALLEDROM[banked.banked.bank];
};

uint8_t MyIntel4001::read(const UBankedAddress address) const {
    return ROM[address.raw & 0x0FFF];
}

void MyIntel4001::setSource(const uint8_t source) {
    this->source = (source < MAX_NUMBER_OF_ROM_CHIPS) ? source : 0;
}

uint4_t MyIntel4001::readFromPort() const {
    if(INSTALLEDROM[source])
        return PORTS[source];
    else return 0;
}

void MyIntel4001::writeToPort(const uint4_t value) {
    if(INSTALLEDROM[source])
        PORTS[source] = value;
}

void MyIntel4001::clearROMWhoIsNotInstalled() {
    uint16_t banks = {installed_banks};

    for(auto chip = 0; chip < MAX_NUMBER_OF_ROM_CHIPS; ++chip, banks >>= 1)
        if(!INSTALLEDROM[chip]) memset(ROM+chip*ROM_CELLS_EACH_CHIP,0,ROM_CELLS_EACH_CHIP);
}

const size_t MyIntel4001::ROM_MEMORY_SIZE = { MAX_NUMBER_OF_ROM_CHIPS * ROM_CELLS_EACH_CHIP };
