#include "GBSerial.h"
#include "GBBus.h"
#include "GBMemoryMap.h"

void GBSerial::Reset()
{
    GBComponent::Reset();
    m_SB = 0x00;
    m_SC = 0x00;
}

void GBSerial::Tick(GBBus* bus, GBInterruptBus* interruptBus)
{
    //check if requested address is in range
    quint16 address = bus->GetAddress();
    if (address == SB_REGISTER || address == SC_REGISTER)
    {
        if(bus->IsReadReqPending())
        {
            bus->SetData(0x00);
            bus->ReadReqAck();
        }
        if (bus->IsWriteReqPending())
        {
            bus->WriteReqAck();
        }
    }
}
