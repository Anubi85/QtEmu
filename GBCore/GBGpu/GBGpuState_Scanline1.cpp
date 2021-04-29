#include "IGBGpuStateContext.h"
#include "GBGpuState_Scanline1.h"

void GBGpuState_Scanline1::Tick(GBBus* bus)
{
    Q_UNUSED(bus)
    if (m_Context->PerformCycle() == 80)
    {
        m_Context->SetState(GpuState::Scanline2);
    }
}
