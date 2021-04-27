#include "IGBGpuStateContext.h"
#include "GBGpuState_Suspended.h"
#include "GBGpuState_Scanline1.h"

GBGpuState_Suspended::GBGpuState_Suspended(IGBGpuStateContext* context) :
    IGBGpuState(context)
{

}

void GBGpuState_Suspended::Tick(GBBus* bus)
{
    Q_UNUSED(bus)
    if (m_Context->IsDisplayEnabled())
    {
        m_Context->SetState(new GBGpuState_Scanline1(m_Context));
    }
}
