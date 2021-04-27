#include "IGBGpuStateContext.h"
#include "GBGpuState_VBlank.h"
#include "GBGpuState_Scanline1.h"
#include "GBGpuState_Suspended.h"

GBGpuState_VBlank::GBGpuState_VBlank(IGBGpuStateContext* context) :
    IGBGpuState(context)
{

}

void GBGpuState_VBlank::Tick(GBBus* bus)
{
    Q_UNUSED(bus)
    if (!m_Context->IsDisplayEnabled())
    {
        m_Context->SetState(new GBGpuState_Suspended(m_Context));
    }
    else if(m_Context->PerformCycle() == 456)
    {
        m_Context->ResetCycles();
        m_Context->IncreaseYLineCount();
        if (m_Context->GetYLineCount() == 0)
        {
            m_Context->FrameReady();
            m_Context->SetState(new GBGpuState_Scanline1(m_Context));
        }
    }
}
