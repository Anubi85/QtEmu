#include "GBCpuState_Decode.h"
#include "GBCpuState_CBFetch.h"
#include "GBCpuState_Execute.h"
#include "GBInstructionContext.h"
#include "GBBus.h"
#include "GBCpu.h"

GBCpuState_Decode::GBCpuState_Decode(GBCpu* context, bool isCB) :
    IGBCpuState (context)
{
    m_IsCB = isCB;
}

void GBCpuState_Decode::Update(GBBus* bus)
{
    if (m_IsCB)
    {
        m_Context->SetState(new GBCpuState_Execute(
                                m_Context,
                                GBCpu::s_CBInstructionTable[bus->GetData()],
                                new GBInstructionContext(bus->GetData())));
    }
    else if (bus->GetData() != 0xCB)
    {
        m_Context->SetState(new GBCpuState_Execute(
                                m_Context,
                                GBCpu::s_InstructionTable[bus->GetData()],
                                new GBInstructionContext(bus->GetData())));
    }
    else
    {
        m_Context->SetState(new GBCpuState_CBFetch(m_Context));
    }
}
