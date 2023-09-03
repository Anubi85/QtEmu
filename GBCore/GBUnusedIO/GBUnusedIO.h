#pragma once

#include "GBComponent.h"

#define UNUSED_IO_ADDRESS_OFFSET 0xFF4C
#define UNUSED_IO_SIZE 0x0034

class GBUnusedIO : public GBComponent
{
private:
	bool IsAddressInRange(quint16 address) { return address >= UNUSED_IO_ADDRESS_OFFSET && address < UNUSED_IO_ADDRESS_OFFSET + UNUSED_IO_SIZE; }
public:
	GBUnusedIO() { Reset(); }
	void Reset() override;
	void Tick(GBBus* bus, GBInterruptBus* interruptBus) override;
};
