#include "GBRam.h"
#include "GBBus.h"

void GBRam::Reset()
{
    GBComponent::Reset();
    memset(m_Ram, 0, RAM_SIZE);
}

void GBRam::ReadData(IGBBus *bus)
{
	if (bus->IsReadReqPending())
	{
		bus->SetData(m_Ram[bus->GetAddress() % RAM_SIZE]);
		bus->ReadReqAck();
	}
}

void GBRam::WriteData(IGBBus *bus)
{
	if (bus->IsWriteReqPending())
	{
		m_Ram[bus->GetAddress() % RAM_SIZE] = bus->GetData();
		bus->WriteReqAck();
	}
}

void GBRam::Tick(GBBus* bus)
{
	if (IsAddressInRange(bus->MainBus()->GetAddress()))
    {
		if (bus->IsDmaActive())
		{
			ReadData(bus->DmaBus());
		}
		ReadData(bus->MainBus());
		WriteData(bus->MainBus());
    }
}
