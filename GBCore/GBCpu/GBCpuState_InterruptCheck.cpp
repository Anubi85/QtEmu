#include "GBCpuState_InterruptCheck.h"
#include "GBBus.h"
#include "IGBCpuStateContext.h"

void GBCpuState_InterruptCheck::Update(GBBus* bus)
{
    m_Context->ResetInterruptMode();
    //check for interrupts
	if (m_Context->GetImeFlag() && bus->InterruptBus()->GetInterrupts() != 0)
    {
        for (int interrupt = 0; interrupt < INTERRUPT_NUM; interrupt++)
        {
            int interruptMask = 1 << interrupt;
			if ((bus->InterruptBus()->GetInterrupts() & interruptMask) != 0)
            {
                //Acknowledge the interrupt
				bus->InterruptBus()->SetInterruptAcq(static_cast<Interrupt>(interruptMask));
                //notify to CPU that we are handling interrupt
                m_Context->SetInterruptMode(s_InterruptRoutineAddress[interrupt]);
                break;
            }
        }
    }
    m_Context->SetState(CpuState::Fetch);
}
