#include "IGBVideoStateContext.h"
#include "GBVideoState_Scanline1.h"
#include "GBVideoState_Scanline2.h"

GBVideoState_Scanline1::GBVideoState_Scanline1(IGBVideoStateContext* context) :
    IGBVideoState(context)
{

}

void GBVideoState_Scanline1::Tick(GBBus* bus)
{
    Q_UNUSED(bus)
    if (m_Context->PerformCycle() == 80)
    {
        m_Context->SetState(new GBVideoState_Scanline2(m_Context));
    }
}
