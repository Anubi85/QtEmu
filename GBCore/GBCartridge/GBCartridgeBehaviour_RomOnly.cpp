#include "GBCartridgeBehaviour_RomOnly.h"
#include "GBBus.h"

void GBCartridgeBehaviour_RomOnly::ProcessRomRequests(IGBBus *bus)
{
	if (bus->GetAddress() < CARTRIDGE_ROM_SIZE)
	{
		if (bus->IsReadReqPending())
		{
			bus->SetData(m_Data[bus->GetAddress()]);
			bus->ReadReqAck();
		}
		if (bus->IsWriteReqPending())
		{
			//ignore the write requests, we are a ROM only cartridge
			bus->WriteReqAck();
		}
	}
}

void GBCartridgeBehaviour_RomOnly::ProcessRequests(GBBus* bus)
{
	if (bus->IsDmaActive())
	{
		ProcessRomRequests(bus->DmaBus());
	}
	ProcessRomRequests(bus->MainBus());
}
