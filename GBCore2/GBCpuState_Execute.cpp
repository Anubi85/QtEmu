#include "GBCpuState_Execute.h"
#include "GBCpuState_InterruptCheck.h"
#include "GBInstructionContext.h"
#include "GBCpu.h"

GBCpuState_Execute::GBCpuState_Execute(GBCpu* context, GBInstruction inst, GBInstructionContext* instContext) :
    IGBCpuState (context)
{
    m_Instruction = inst;
    m_InstructionContext = instContext;
    m_Count = 0;
}

void GBCpuState_Execute::Update(GBBus* bus)
{
    if (m_Count-- == 0)
    {
        if ((m_Context->*m_Instruction)(m_InstructionContext, bus))
        {
            delete m_InstructionContext;
            m_Context->SetState(new GBCpuState_InterruptCheck(m_Context));
        }
        else
        {
            //wait for 3 cycles (until next Execute)
            m_Count = 3;
        }
    }
}
