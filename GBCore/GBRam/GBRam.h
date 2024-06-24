#pragma once

#include <QtGlobal>
#include "GBComponent.h"
#include "GBMemoryMap.h"

class IGBBus;

class GBRam : public GBComponent
{
private:
    quint8 m_Ram[RAM_SIZE];

	bool IsAddressInRange(quint16 address) { return address >= RAM_ADDRESS && address < RAM_ADDRESS + RAM_SIZE + RAM_ECHO_SIZE; }
public:
    GBRam() { Reset(); }
    void Reset() override;
	void ReadData(IGBBus* bus);
	void WriteData(IGBBus* bus);
	void Tick(GBBus* bus) override;
};
