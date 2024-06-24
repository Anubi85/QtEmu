#include "GBBus.h"
#include "GBInterruptBus.h"
#include "GBInternalBus.h"

GBBus::GBBus()
{
	m_MainBus = new GBSharedBus(false, m_SharedBusData);
	m_DmaBus = new GBSharedBus(true, m_SharedBusData);
	m_InterruptBus = new GBInterruptBus();
	m_GpuBus = new GBInternalBus();
}

GBBus::~GBBus()
{
	delete m_MainBus;
	delete m_DmaBus;
	delete m_InterruptBus;
}

void GBBus::Clear()
{
	m_SharedBusData.IsDmaActive = false;
	m_SharedBusData.DmaAddress = 0x0000;
	m_SharedBusData.MainAddress = 0x0000;
	m_SharedBusData.DmaData = 0x00;
	m_SharedBusData.MainData = 0x00;
	reinterpret_cast<GBSharedBus*>(m_MainBus)->Clear();
	reinterpret_cast<GBSharedBus*>(m_DmaBus)->Clear();
	m_InterruptBus->Clear();
	reinterpret_cast<GBInternalBus*>(m_GpuBus)->Clear();
}
