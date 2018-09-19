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
    //check if a read or write request is pending
    if (bus->IsReadReqPending() || bus->IsWriteReqPending())
    {
        //check if the address is in range of video RAM
        if (bus->GetAddress() >= ADDRESS_OFFSET && bus->GetAddress() < ADDRESS_OFFSET + VIDEO_RAM_SIZE)
        {
            //check if write request
            if (bus->IsWriteReqPending())
            {
                m_VideoRAM[bus->GetAddress() - ADDRESS_OFFSET] = static_cast<char>(bus->GetData());
                bus->WriteReqAck();
            }
            else //must be a read request, we alredy checked that a request is pending!!
            {
                bus->SetData(static_cast<quint8>(m_VideoRAM[bus->GetAddress() - ADDRESS_OFFSET]));
                bus->ReadReqAck();
            }
        }
    }
}
