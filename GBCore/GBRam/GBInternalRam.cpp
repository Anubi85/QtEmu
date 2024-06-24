#include "GBInternalRam.h"
#include "GBBus.h"

void GBInternalRam::Reset()
{
    GBComponent::Reset();
	memset(m_Ram, 0, HRAM_SIZE);
}

void GBInternalRam::Tick(GBBus* bus)
{
	if (IsAddressInRange(bus->MainBus()->GetAddress()))
    {
		if (bus->MainBus()->IsReadReqPending())
        {
			bus->MainBus()->SetData(m_Ram[bus->MainBus()->GetLocalAddress(HRAM_ADDRESS)]);
			bus->MainBus()->ReadReqAck();
        }
		if (bus->MainBus()->IsWriteReqPending())
        {
			m_Ram[bus->MainBus()->GetLocalAddress(HRAM_ADDRESS)] = bus->MainBus()->GetData();
			bus->MainBus()->WriteReqAck();
        }
    }
}
