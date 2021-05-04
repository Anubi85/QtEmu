#pragma once

#include "GBComponent.h"

class GBInterrupt : public GBComponent
{
private:
	quint8 m_IF;
	quint8 m_IE;
public:
	GBInterrupt() { Reset(); }
	void Reset() override;
    void Tick(GBBus* bus, GBInterruptBus* interruptBus) override;
};
