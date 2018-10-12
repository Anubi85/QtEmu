#include "GBVideo.h"
#include "GBVideoState_Scanline2.h"
#include "GBVideoState_HBlank.h"

GBVideoState_Scanline2::GBVideoState_Scanline2(GBVideo* context) :
    IGBVideoState(context)
{

}

void GBVideoState_Scanline2::Tick()
{
    if (m_Context->PerformCycle() == 80 + 172)
    {
        m_Context->SetState(new GBVideoState_HBlank(m_Context));
    }
}
