#include "GBCartridgeBehaviour_RomOnly.h"
#include "GBBus.h"

void GBCartridgeBehaviour_RomOnly::ProcessRequests(GBBus* bus)
{
    if (bus->IsReadReqPending() && bus->GetAddress() < ROM_ONLY_SIZE)
    {
        bus->SetData(m_Data[bus->GetAddress()]);
        bus->ReadReqAck();
    }
	if (bus->IsWriteReqPending() && bus->GetAddress() < ROM_ONLY_SIZE)
	{
		//ignore the write requests, we are a ROM only cartridge
		bus->WriteReqAck();
	}
}
