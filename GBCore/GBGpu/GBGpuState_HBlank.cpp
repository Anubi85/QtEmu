#include "IGBGpuStateContext.h"
#include "GBGpuState_HBlank.h"

void GBGpuState_HBlank::Tick(GBBus* bus)
{
    Q_UNUSED(bus)
    if ((m_Context->PerformCycle() % 456) == 0)
    {
        m_Context->ResetCycles();
        m_Context->IncreaseYLineCount();
        if (m_Context->GetYLineCount() == VIDEO_MAX_HBLANK)
        {
            m_Context->SetState(GpuState::VBlank);
        }
        else
        {
            m_Context->SetState(GpuState::Scanline1);
        }
    }
}
