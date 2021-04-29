#include "GBCartridgeBehaviour_RomOnly.h"
#include "GBBus.h"

void GBCartridgeBehaviour_RomOnly::ProcessRequests(GBBus* bus)
{
    if (bus->IsReadReqPending() && bus->GetAddress() < ROM_ONLY_SIZE)
    {
        bus->SetData(m_Data[bus->GetAddress()]);
        bus->ReadReqAck();
    }
}
