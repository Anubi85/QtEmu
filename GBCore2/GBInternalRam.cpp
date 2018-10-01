#include "GBInternalRam.h"
#include "GBBus.h"

GBInternalRam::GBInternalRam() :
    m_Ram(INTERNAL_RAM_SIZE, 0)
{
    Reset();
}

void GBInternalRam::Reset()
{
    m_Ram.fill(0);
}

void GBInternalRam::Tick(GBBus* bus)
{
    if (IsAddressInRange(bus->GetAddress()))
    {
        if (bus->IsReadReqPending())
        {
            bus->SetData(static_cast<quint8>(m_Ram[bus->GetAddress() - INTERNAL_RAM_ADDRESS_OFFSET]));
            bus->ReadReqAck();
        }
        if (bus->IsWriteReqPending())
        {
            m_Ram[bus->GetAddress() - INTERNAL_RAM_ADDRESS_OFFSET] = static_cast<char>(bus->GetData());
            bus->WriteReqAck();
        }
    }
}
