#include "GBInterrupt.h"
#include "GBBus.h"
#include "GBInterruptBus.h"
#include "GBMemoryMap.h"

void GBInterrupt::Reset()
{
	GBComponent::Reset();
	m_IF = 0;
	m_IE = 0;
}

void GBInterrupt::Tick(GBBus* bus)
{
	//Handle interrupt requests and acknowledge
	m_IF &= bus->InterruptBus()->GetInterruptsAck();
	bus->InterruptBus()->SetInterruptAcq(Interrupt::None);
	m_IF |= bus->InterruptBus()->GetInterruptsReq();
	bus->InterruptBus()->SetInterruptReq(Interrupt::None);
	//Handle read/write to registers
	if (bus->MainBus()->IsReadReqPending())
	{
		switch (bus->MainBus()->GetAddress())
		{
			case IF_REGISTER:
				bus->MainBus()->ReadReqAck();
				bus->MainBus()->SetData(m_IF & 0x1F);
				break;
			case IE_REGISTER:
				bus->MainBus()->ReadReqAck();
				bus->MainBus()->SetData(m_IE & 0x1F);
				break;
		}
	}
	if (bus->MainBus()->IsWriteReqPending())
	{
		switch (bus->MainBus()->GetAddress())
		{
			case IF_REGISTER:
				bus->MainBus()->WriteReqAck();
				m_IF = bus->MainBus()->GetData() & 0x1F;
				break;
			case IE_REGISTER:
				bus->MainBus()->WriteReqAck();
				m_IE = bus->MainBus()->GetData() & 0x1F;
				break;
		}
	}
	//Notify active interrupts
	bus->InterruptBus()->SetInterrupts(m_IF & m_IE & 0x1F);
}
