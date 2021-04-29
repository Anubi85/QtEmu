#include "GBCpuState_Decode.h"
#include "GBInstructionContext.h"
#include "GBBus.h"
#include "IGBCpuStateContext.h"

void GBCpuState_Decode::Update(GBBus* bus)
{
    if (bus->GetData() == 0xCB)
    {
        m_Context->SetCBFlag(true);
        //TODO: serve?
        m_Context->SetOpCode(NOP_INSTRUCTION);
        m_Context->SetState(CpuState::Fetch);
    }
    else
    {
        m_Context->SetOpCode(bus->GetData());
        m_Context->SetState(CpuState::Execute);
    }
}
