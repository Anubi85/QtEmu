#include "GBCpuState_Decode.h"
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
        GBCpu::s_CBInstructionTable[bus->GetData()];
    }
    else
    {
        GBCpu::s_InstructionTable[bus->GetData()];
    }
}
