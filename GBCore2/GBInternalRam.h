#ifndef GBINTERNALRAM_H
#define GBINTERNALRAM_H

#include <QtCore>
#include "GBComponent.h"

#define INTERNAL_RAM_SIZE 0x0080
#define INTERNAL_RAM_ADDRESS_OFFSET 0xFF80

class GBInternalRam : public GBComponent
{
private:
    quint8 m_Ram[INTERNAL_RAM_SIZE];

    bool IsAddressInRange(quint16 address) { return address >= INTERNAL_RAM_ADDRESS_OFFSET; }
public:
    GBInternalRam();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBINTERNALRAM_H
