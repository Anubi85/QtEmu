#include "IGBGpuStateContext.h"
#include "GBGpuState_Suspended.h"

void GBGpuState_Suspended::Tick(IGBBus* bus)
{
    Q_UNUSED(bus)
    if (m_Context->IsDisplayEnabled())
    {
        m_Context->SetState(GpuState::Scanline1);
    }
}
