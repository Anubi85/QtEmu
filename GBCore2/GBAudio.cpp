#include "GBAudio.h"
#include "GBBus.h"

GBAudio::GBAudio()
{
    Reset();
}

void GBAudio::Reset()
{
    m_NR52 = 0x81; //audio enabled, channel 1 enabled
}

bool GBAudio::IsAddressInRange(quint16 address)
{
    bool result = false;
    result |= address == NR52_ADDRESS;
    return result;
}

void GBAudio::Tick(GBBus* bus)
{
    //check if a read request is pending and the address is in range
    if (bus->IsReadReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        switch (bus->GetAddress())
        {
        case NR52_ADDRESS:
            bus->SetData(m_NR52 | 0x70);
            break;
        }
        bus->ReadReqAck();
    }
    //check if a write request is pending and the address is in range
    if (bus->IsWriteReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        switch (bus->GetAddress())
        {
        case NR52_ADDRESS:
            m_NR52 = bus->GetData() & 0x80;
            //resetta i contenuti di tutti i registri audio quando disabilito il suono
            //se suono disabilitato gli altri registri non sono acessibili
            break;
        }
        bus->WriteReqAck();
    }
}
