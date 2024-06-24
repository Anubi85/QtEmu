#pragma once

#include <QtGlobal>

#define DELAY_CYCLES_NUM 4
#define TOTAL_CYCLES_NUM 640

class GBBus;

class GBDma
{
private:
	bool m_DmaStarted;
	qint16 m_CycleCount;
	quint16 m_SourceAddress;
	quint16 m_DestinationAddress;
public:
	GBDma() { Reset(); }
	void Reset();
	void Start(quint8 startAddress);
	void Tick(GBBus* bus);
};
