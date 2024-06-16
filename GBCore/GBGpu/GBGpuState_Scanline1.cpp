#include "IGBGpuStateContext.h"
#include "GBGpuState_Scanline1.h"

void GBGpuState_Scanline1::Tick(GBBus* bus)
{
    Q_UNUSED(bus)
    if (m_Context->PerformCycle() == 80)
    {
		//draw the window if it is active and we are at the correct line
		m_Context->ActivateWindow(m_Context->IsWindowEnabled() & (m_Context->GetYLineCount() == m_Context->GetWindowYCoord()));
        m_Context->SetState(GpuState::Scanline2);
    }
}
