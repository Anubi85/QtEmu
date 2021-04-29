#include "IGBGpuStateContext.h"
#include "GBGpuState_Suspended.h"

void GBGpuState_Suspended::Tick(GBBus* bus)
{
    Q_UNUSED(bus)
    if (m_Context->IsDisplayEnabled())
    {
        m_Context->SetState(GpuState::Scanline1);
    }
}
