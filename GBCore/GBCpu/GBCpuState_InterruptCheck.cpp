#include "GBCpuState_InterruptCheck.h"
#include "GBInterruptBus.h"
#include "IGBCpuStateContext.h"

void GBCpuState_InterruptCheck::Update(GBBus* bus, GBInterruptBus* interruptBus)
{
    Q_UNUSED(bus)
    m_Context->ResetInterruptMode();
    //check for interrupts
    if (m_Context->GetImeFlag() && interruptBus->GetInterrupts() != 0)
    {
        for (int interrupt = 0; interrupt < INTERRUPT_NUM; interrupt++)
        {
            int interruptMask = 1 << interrupt;
            if ((interruptBus->GetInterrupts() & interruptMask) != 0)
            {
                //Acknowledge the interrupt
                interruptBus->SetInterruptAcq(static_cast<Interrupt>(interruptMask));
                //notify to CPU that we are handling interrupt
                m_Context->SetInterruptMode(s_InterruptRoutineAddress[interrupt]);
                break;
            }
        }
    }
    m_Context->SetState(CpuState::Fetch);
}
