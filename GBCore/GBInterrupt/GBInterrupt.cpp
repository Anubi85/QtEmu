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

void GBInterrupt::Tick(GBBus *bus, GBInterruptBus* interruptBus)
{
	//Handle interrupt requests and acknowledge
        m_IF &= interruptBus->GetInterruptsAck();
        interruptBus->SetInterruptAcq(Interrupt::None);
        m_IF |= interruptBus->GetInterruptsReq();
        interruptBus->SetInterruptReq(Interrupt::None);
	//Handle read/write to registers
	if (bus->IsReadReqPending())
	{
		switch (bus->GetAddress())
		{
			case IF_REGISTER:
				bus->ReadReqAck();
				bus->SetData(m_IF & 0x1F);
				break;
			case IE_REGISTER:
				bus->ReadReqAck();
				bus->SetData(m_IE & 0x1F);
				break;
		}
	}
	if (bus->IsWriteReqPending())
	{
		switch (bus->GetAddress())
		{
			case IF_REGISTER:
				bus->WriteReqAck();
				m_IF = bus->GetData() & 0x1F;
				break;
			case IE_REGISTER:
				bus->WriteReqAck();
				m_IE = bus->GetData() & 0x1F;
				break;
		}
	}
	//Notify active interrupts
        interruptBus->SetInterrupts(m_IF & m_IE & 0x1F);
}
