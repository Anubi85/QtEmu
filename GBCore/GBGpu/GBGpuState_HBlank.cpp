#include "IGBGpuStateContext.h"
#include "GBGpuState_HBlank.h"
#include "GBGpuState_Scanline1.h"
#include "GBGpuState_VBlank.h"

GBGpuState_HBlank::GBGpuState_HBlank(IGBGpuStateContext* context) :
    IGBGpuState(context)
{

}

void GBGpuState_HBlank::Tick(GBBus* bus)
{
    Q_UNUSED(bus)
    if ((m_Context->PerformCycle() % 456) == 0)
    {
        m_Context->ResetCycles();
        m_Context->IncreaseYLineCount();
        if (m_Context->GetYLineCount() == VIDEO_MAX_HBLANK)
        {
            m_Context->SetState(new GBGpuState_VBlank(m_Context));
        }
        else
        {
            m_Context->SetState(new GBGpuState_Scanline1(m_Context));
        }
    }
}
