#include "GBInternalRam.h"
#include "GBBus.h"

GBInternalRam::GBInternalRam()
{
    Reset();
}

void GBInternalRam::Reset()
{
    GBComponent::Reset();
    memset(m_Ram, 0, INTERNAL_RAM_SIZE);
}

void GBInternalRam::Tick(GBBus* bus)
{
    if (IsAddressInRange(bus->GetAddress()))
    {
        if (bus->IsReadReqPending())
        {
            bus->SetData(m_Ram[bus->GetAddress() - INTERNAL_RAM_ADDRESS_OFFSET]);
            bus->ReadReqAck();
        }
        if (bus->IsWriteReqPending())
        {
            m_Ram[bus->GetAddress() - INTERNAL_RAM_ADDRESS_OFFSET] = bus->GetData();
            bus->WriteReqAck();
        }
    }
}
