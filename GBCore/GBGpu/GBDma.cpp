#include "GBDma.h"
#include "GBBus.h"
#include "GBMemoryMap.h"

void GBDma::Reset()
{
	m_DmaStarted = false;
	m_CycleCount = 0;
	m_SourceAddress = 0x0000;
	m_DestinationAddress = OAM_ADDRESS;
}

void GBDma::Start(quint8 startAddress)
{
	m_DmaStarted = true;
	m_CycleCount = -DELAY_CYCLES_NUM;
	m_SourceAddress = static_cast<quint16>(startAddress << 8);
	m_DestinationAddress = OAM_ADDRESS;
}

void GBDma::Tick(GBBus *bus)
{
	if (m_DmaStarted)
	{
		if (m_CycleCount == 0)
		{
			bus->ActivateDma(true);
		}
		else if (m_CycleCount == TOTAL_CYCLES_NUM)
		{
			bus->ActivateDma(false);
			m_DmaStarted = false;
		}
		switch (m_CycleCount % 4)
		{
			case 0:
				bus->DmaBus()->SetAddress(m_SourceAddress);
				bus->DmaBus()->RequestRead();
				break;
			case 1:
				m_SourceAddress++;
				break;
			case 2:
				bus->DmaBus()->SetAddress(m_DestinationAddress);
				bus->DmaBus()->RequestWrite();
				break;
			case 3:
				m_DestinationAddress++;
				break;
		}
	}
}
