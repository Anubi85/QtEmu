#include "GBInternalRam.h"
#include "GBBus.h"

void GBInternalRam::Reset()
{
    GBComponent::Reset();
	memset(m_Ram, 0, HRAM_SIZE);
}

void GBInternalRam::Tick(GBBus* bus, GBInterruptBus* interruptBus)
{
    Q_UNUSED(interruptBus)
    if (IsAddressInRange(bus->GetAddress()))
    {
        if (bus->IsReadReqPending())
        {
			bus->SetData(m_Ram[bus->GetAddress() - HRAM_ADDRESS]);
            bus->ReadReqAck();
        }
        if (bus->IsWriteReqPending())
        {
			m_Ram[bus->GetAddress() - HRAM_ADDRESS] = bus->GetData();
            bus->WriteReqAck();
        }
    }
}
