#include "GBCpuState_Decode.h"
#include "GBInstructionContext.h"
#include "GBBus.h"
#include "IGBCpuStateContext.h"

void GBCpuState_Decode::Update(GBBus* bus)
{
    if (m_Context->IsHandlingInterrupt())
    {
        //force execution of a CALL without condition, opcode 0xCD
        m_Context->SetOpCode(0xCD);
        m_Context->SetState(CpuState::Execute);
    }
    else
    {
		quint8 data = bus->MainBus()->GetData();
		if (data == 0xCB)
        {
            m_Context->SetCBFlag(true);
            m_Context->SetState(CpuState::Fetch);
        }
        else
        {
			m_Context->SetOpCode(data);
            m_Context->SetState(CpuState::Execute);
        }
    }
}
