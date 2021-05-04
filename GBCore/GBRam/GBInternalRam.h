#pragma once

#include <QtGlobal>
#include "GBComponent.h"
#include "GBMemoryMap.h"

class GBInternalRam : public GBComponent
{
private:
	quint8 m_Ram[HRAM_SIZE];

	bool IsAddressInRange(quint16 address) { return address >= HRAM_ADDRESS && address < HRAM_ADDRESS + HRAM_SIZE; }
public:
    GBInternalRam() { Reset(); }
    void Reset() override;
    void Tick(GBBus* bus, GBInterruptBus* interruptBus) override;
};
