#include "GBCpuState_Decode.h"
#include "GBInstructionContext.h"
#include "GBBus.h"
#include "IGBCpuStateContext.h"

void GBCpuState_Decode::Update(GBBus* bus, GBInterruptBus* interruptBus)
{
    Q_UNUSED(interruptBus)
    if (m_Context->IsHandlingInterrupt())
    {
        //force execution of a CALL without condition, opcode 0xCD
        m_Context->SetOpCode(0xCD);
        m_Context->SetState(CpuState::Execute);
    }
    else
    {
        if (bus->GetData() == 0xCB)
        {
            m_Context->SetCBFlag(true);
            m_Context->SetState(CpuState::Fetch);
        }
        else
        {
            m_Context->SetOpCode(bus->GetData());
            m_Context->SetState(CpuState::Execute);
        }
    }
}
