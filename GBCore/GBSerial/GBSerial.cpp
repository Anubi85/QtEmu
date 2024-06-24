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

void GBSerial::Tick(GBBus* bus)
{
    //check if requested address is in range
	if(bus->MainBus()->IsReadReqPending())
	{
		switch (bus->MainBus()->GetAddress())
		{
			case SB_REGISTER:
				bus->MainBus()->ReadReqAck();
				bus->MainBus()->SetData(m_SB);
				break;
			case SC_REGISTER:
				bus->MainBus()->ReadReqAck();
				bus->MainBus()->SetData(m_SC | 0x7E);
				break;
		}
	}
	if (bus->MainBus()->IsWriteReqPending())
	{
		switch (bus->MainBus()->GetAddress())
		{
			case SB_REGISTER:
				bus->MainBus()->WriteReqAck();
				m_SB = bus->MainBus()->GetData();
				break;
			case SC_REGISTER:
				bus->MainBus()->WriteReqAck();
				m_SC = bus->MainBus()->GetData() & 0x81;
				if (m_SC & 0x80)
				{
					m_BitCounter = 0;
					m_IsTransferingData = true;
				}
				break;
		}
	}
    if (m_IsTransferingData)
    {
        if (++m_BitCounter == 8)
        {
            m_IsTransferingData = false;
            m_SC &= 0x7F;
			bus->InterruptBus()->SetInterruptReq(Interrupt::SerialTransfer);
        }
        bool toSend = (m_SB & 0x01) != 0;
        //TODO: transfer and receive
        bool received = true;
        m_SB >>= 1;
        m_SB |= (received ? 0x80 : 0x00);
    }
}
