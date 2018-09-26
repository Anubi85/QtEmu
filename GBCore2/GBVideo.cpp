#include "GBVideo.h"
#include "GBBus.h"

GBVideo::GBVideo() :
    m_Registers(VIDEO_REG_SIZE, 0),
    m_VideoRAM(VIDEO_RAM_SIZE, 0)
{
    Reset();
}

void GBVideo::Reset()
{
    GBComponent::Reset();
    m_VideoRAM.fill(0);
    m_Registers.fill(0);
}

void GBVideo::Tick(GBBus* bus)
{
    //check if a read request is pending and address is in range
    if (bus->IsReadReqPending())
    {
        if (IsAddressInVideoRAM(bus->GetAddress()))
        {
            bus->SetData(static_cast<quint8>(m_VideoRAM[bus->GetAddress() - VIDEO_RAM_ADDRESS_OFFSET]));
            bus->ReadReqAck();
        }
    }
    //check if a write request is pending and address is in range
    if (bus->IsWriteReqPending())
    {
        if (IsAddressInVideoRAM(bus->GetAddress()))
        {
            m_VideoRAM[bus->GetAddress() - VIDEO_RAM_ADDRESS_OFFSET] = static_cast<char>(bus->GetData());
            bus->WriteReqAck();
        }
    }
}
