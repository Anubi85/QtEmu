#include "GBUnusedIO.h"
#include "GBBus.h"

void GBUnusedIO::Reset()
{
	GBComponent::Reset();
}

void GBUnusedIO::Tick(GBBus* bus)
{
	if (IsAddressInRange(bus->MainBus()->GetAddress()))
	{
		if (bus->MainBus()->IsReadReqPending())
		{
			bus->MainBus()->SetData(0xFF);
			bus->MainBus()->ReadReqAck();
		}
		if (bus->MainBus()->IsWriteReqPending())
		{
			bus->MainBus()->WriteReqAck();
		}
	}
}
