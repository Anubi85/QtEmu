#include "GBCpuState_Decode.h"
#include "GBCpuState_Fetch.h"
#include "GBCpuState_Execute.h"
#include "GBCpuState_Error.h"
#include "GBInstructionContext.h"
#include "GBBus.h"
#include "IGBCpuStateContext.h"

GBCpuState_Decode::GBCpuState_Decode(IGBCpuStateContext* context, bool isCB) :
    IGBCpuState (context)
{
    m_IsCB = isCB;
}

void GBCpuState_Decode::Update(GBBus* bus)
{
    if (bus->GetData() == 0xCB)
    {
        m_Context->SetState(new GBCpuState_Fetch(m_Context, true));
    }
    else
    {
        GBInstruction inst = m_IsCB ? m_Context->GetCBInstruction(bus->GetData()) : m_Context->GetInstruction(bus->GetData());
        if (inst != nullptr)
        {
            m_Context->SetState(new GBCpuState_Execute(
                                    m_Context,
                                    inst,
                                    new GBInstructionContext(bus->GetData())));
        }
        else
        {
            QString msg("Op Code %1 not implemented");
            m_Context->SetState(new GBCpuState_Error(m_Context, msg.arg(m_IsCB ? "0xCB 0x%1" : "0x%1").arg(bus->GetData(), 2, 16, QLatin1Char('0'))));
        }
    }
}
