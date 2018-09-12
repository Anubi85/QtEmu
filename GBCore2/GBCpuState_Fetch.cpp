#include "GBCpuState_Fetch.h"
#include "GBCpuState_Decode.h"
#include "GBBus.h"
#include "GBCpu.h"

GBCpuState_Fetch::GBCpuState_Fetch(GBCpu* context) :
    IGBCpuState (context)
{

}

void GBCpuState_Fetch::Update(GBBus* bus)
{
    bus->SetAddress(m_Context->m_PC++);
    bus->RequestRead();
    m_Context->SetState(new GBCpuState_Decode(m_Context));
    delete this;
}
