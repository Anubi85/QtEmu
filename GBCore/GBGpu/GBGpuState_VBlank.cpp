#include "IGBGpuStateContext.h"
#include "GBGpuState_VBlank.h"

void GBGpuState_VBlank::Tick(GBBus* bus)
{
    Q_UNUSED(bus)
    if (!m_Context->IsDisplayEnabled())
    {
        m_Context->SetState(GpuState::Suspended);
    }
    else if(m_Context->PerformCycle() == 456)
    {
        m_Context->ResetCycles();
        m_Context->IncreaseYLineCount();
        if (m_Context->GetYLineCount() == 0)
        {
            m_Context->FrameReady();
            m_Context->SetState(GpuState::Scanline1);
        }
    }
}
