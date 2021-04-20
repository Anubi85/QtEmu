#include "GBCpuState_Execute.h"
#include "GBCpuState_InterruptCheck.h"
#include "GBInstructionContext.h"
#include "IGBCpuStateContext.h"

void GBCpuState_Execute::Reset()
{
    m_InstructionContext.SetOpCode(m_Context->GetOpCode());
    m_Count = 0;
}

void GBCpuState_Execute::Update(GBBus* bus)
{
    if (m_Count-- == 0)
    {
        if (m_Context->ExecuteOpCode(&m_InstructionContext, bus))
        {
            m_Context->SetState(CpuState::InterruptCheck, false, NOP_INSTRUCTION);
        }
        else
        {
            //wait for 3 cycles (until next Execute)
            m_Count = 3;
        }
    }
}
