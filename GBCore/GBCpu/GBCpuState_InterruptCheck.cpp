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
    m_Context->SetState(CpuState::Fetch);
}
