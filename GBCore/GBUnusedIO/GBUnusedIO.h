#pragma once

#include "GBComponent.h"
#include "GBMemoryMap.h"

class GBUnusedIO : public GBComponent
{
private:
	bool IsAddressInRange(quint16 address) { return address >= IO_UNUSED_REGISTERS_ADDRESS && address < IO_UNUSED_REGISTERS_ADDRESS + IO_UNUSED_REGISTERS_SIZE; }
public:
	GBUnusedIO() { Reset(); }
	void Reset() override;
	void Tick(GBBus* bus) override;
};
