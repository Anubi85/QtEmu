#include "GBSerial.h"
#include "GBBus.h"
#include "GBInterruptBus.h"
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
            if (address == SB_REGISTER)
            {
                bus->SetData(m_SB);
            }
            else
            {
                bus->SetData(m_SC | 0x7E);
            }
            bus->ReadReqAck();
        }
        if (bus->IsWriteReqPending())
        {
            if (address == SB_REGISTER)
            {
                m_SB = bus->GetData();
            }
            else
            {
                m_SC = bus->GetData() & 0x81;
                if (m_SC & 0x80)
                {
                    m_BitCounter = 0;
                    m_IsTransferingData = true;
                }
            }
            bus->WriteReqAck();
        }
    }
    if (m_IsTransferingData)
    {
        if (++m_BitCounter == 8)
        {
            m_IsTransferingData = false;
            m_SC &= 0x7F;
            interruptBus->SetInterruptReq(Interrupt::SerialTransfer);
        }
        bool toSend = (m_SB & 0x01) != 0;
        //TODO: transfer and receive
        bool received = true;
        m_SB >>= 1;
        m_SB |= (received ? 0x80 : 0x00);
    }
}
