#pragma once

#include <QtGlobal>
#include "GBComponent.h"

#define RAM_SIZE 0x2000
#define RAM_OFFSET 0xC000
#define RAM_ECHO_SIZE 0x1E00

class GBRam : public GBComponent
{
private:
    quint8 m_Ram[RAM_SIZE];

    bool IsAddressInRange(quint16 address) { return address >= RAM_OFFSET && address < RAM_OFFSET + RAM_SIZE + RAM_ECHO_SIZE; }
public:
    GBRam() { Reset(); }
    void Reset() override;
    void Tick(GBBus* bus, GBInterruptBus* interruptBus) override;
};
