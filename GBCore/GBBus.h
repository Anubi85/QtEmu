#pragma once

#include "GBSharedBus.h"

class GBInterruptBus;
class GBInternalBus;

class GBBus
{
private:
	GBSharedBusData m_SharedBusData;
	IGBBus* m_MainBus;
	IGBBus* m_DmaBus;
	GBInterruptBus* m_InterruptBus;
	IGBBus* m_GpuBus;
public:
	GBBus();
	~GBBus();
	void Clear();
	IGBBus* MainBus() { return m_MainBus; }
	IGBBus* DmaBus() { return m_DmaBus; }
	void ActivateDma(bool activate) { m_SharedBusData.IsDmaActive = activate; }
	bool IsDmaActive() { return m_SharedBusData.IsDmaActive; }
	GBInterruptBus* InterruptBus() { return m_InterruptBus; }
	IGBBus* GpuBus() { return m_GpuBus; }
};
