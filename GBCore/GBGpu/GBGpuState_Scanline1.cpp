#include "IGBGpuStateContext.h"
#include "GBGpuState_Scanline1.h"
#include "GBGpuState_Scanline2.h"

GBGpuState_Scanline1::GBGpuState_Scanline1(IGBGpuStateContext* context) :
    IGBGpuState(context)
{

}

void GBGpuState_Scanline1::Tick(GBBus* bus)
{
    Q_UNUSED(bus)
    if (m_Context->PerformCycle() == 80)
    {
        m_Context->SetState(new GBGpuState_Scanline2(m_Context));
    }
}
