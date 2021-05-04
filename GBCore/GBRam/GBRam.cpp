#include "GBRam.h"
#include "GBBus.h"

void GBRam::Reset()
{
    GBComponent::Reset();
    memset(m_Ram, 0, RAM_SIZE);
}

void GBRam::Tick(GBBus* bus, GBInterruptBus* interruptBus)
{
    Q_UNUSED(interruptBus)
    if (IsAddressInRange(bus->GetAddress()))
    {
        if (bus->IsReadReqPending())
        {
            bus->SetData(m_Ram[bus->GetAddress() % RAM_SIZE]);
            bus->ReadReqAck();
        }
        if (bus->IsWriteReqPending())
        {
            m_Ram[bus->GetAddress() % RAM_SIZE] = bus->GetData();
            bus->WriteReqAck();
        }
    }
}
