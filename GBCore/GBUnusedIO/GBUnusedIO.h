#pragma once

#include "GBComponent.h"
#include "GBMemoryMap.h"

class GBUnusedIO : public GBComponent
{
private:
	bool IsAddressInRange(quint16 address);
public:
	GBUnusedIO() { Reset(); }
	void Reset() override;
	void Tick(GBBus* bus) override;
};
