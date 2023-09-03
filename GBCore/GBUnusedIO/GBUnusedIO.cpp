#include "GBUnusedIO.h"
#include "GBBus.h"

void GBUnusedIO::Reset()
{
	GBComponent::Reset();
}

void GBUnusedIO::Tick(GBBus* bus, GBInterruptBus* interruptBus)
{
	Q_UNUSED(interruptBus)
	if (IsAddressInRange(bus->GetAddress()))
	{
		if (bus->IsReadReqPending())
		{
			bus->SetData(0xFF);
			bus->ReadReqAck();
		}
		if (bus->IsWriteReqPending())
		{
			bus->WriteReqAck();
		}
	}
}
