#include "GBLcdDisplay.h"
#include "GBBus.h"

GBLcdDisplay::GBLcdDisplay() :
    m_VideoRAM(VIDEO_RAM_SIZE, 0)
{
    Reset();
}

void GBLcdDisplay::Reset()
{
    m_VideoRAM.fill(0);
}

void GBLcdDisplay::Tick(GBBus* bus)
{
    //check if a read request is pending and address is in range
    if (bus->IsReadReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        bus->SetData(static_cast<quint8>(m_VideoRAM[bus->GetAddress() - VIDEO_ADDRESS_OFFSET]));
        bus->ReadReqAck();
    }
    //check if a write request is pending and address is in range
    if (bus->IsWriteReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        m_VideoRAM[bus->GetAddress() - VIDEO_ADDRESS_OFFSET] = static_cast<char>(bus->GetData());
        bus->WriteReqAck();
    }
}
