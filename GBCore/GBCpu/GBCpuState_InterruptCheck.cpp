#include "GBCpuState_InterruptCheck.h"
#include "GBCpuState_Fetch.h"
#include "GBBus.h"
#include "IGBCpuStateContext.h"

GBCpuState_InterruptCheck::GBCpuState_InterruptCheck(IGBCpuStateContext* context) :
    IGBCpuState (context)
{

}

void GBCpuState_InterruptCheck::Update(GBBus* bus)
{
    if (m_Context->GetImeFlag())
    {
        bus->SetAddress(0xFFFF); //read interrupt flags register
        bus->RequestRead();
    }
    //TODO: serve?
    m_Context->SetOpCode(NOP_INSTRUCTION);
    m_Context->SetState(CpuState::Fetch);
}
