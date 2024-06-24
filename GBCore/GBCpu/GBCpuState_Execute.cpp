#include "GBCpuState_Execute.h"
#include "GBCpuState_InterruptCheck.h"
#include "GBInstructionContext.h"
#include "IGBCpuStateContext.h"
#include "GBBus.h"

void GBCpuState_Execute::Reset()
{
    m_InstructionContext.SetOpCode(m_Context->GetOpCode());
    m_Count = 0;
}

void GBCpuState_Execute::Update(GBBus* bus)
{
    if (m_Count-- == 0)
    {
		if (m_Context->ExecuteOpCode(&m_InstructionContext, bus->MainBus()))
        {
            //clean up context before moving ot next state
            m_Context->SetCBFlag(false);
            m_Context->SetOpCode(NOP_INSTRUCTION);
            m_Context->SetState(CpuState::InterruptCheck);
        }
        else
        {
            //wait for 3 cycles (until next Execute)
            m_Count = 3;
        }
    }
}
