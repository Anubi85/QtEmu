#include "GBCpuState_CBFetch.h"
#include "GBCpuState_Decode.h"
#include "GBBus.h"
#include "GBCpu.h"

GBCpuState_CBFetch::GBCpuState_CBFetch(GBCpu* context) :
    IGBCpuState (context)
{
    m_Count = 3; //cpu cycle that has to be skipped
}

void GBCpuState_CBFetch::Update(GBBus* bus)
{
    if (--m_Count == 0)
    {
        bus->SetAddress(m_Context->m_PC++);
        bus->RequestRead();
        m_Context->SetState(new GBCpuState_Decode(m_Context, true));
    }
}
