#include "GBVideo.h"
#include "GBVideoState_Scanline1.h"
#include "GBVideoState_Scanline2.h"

GBVideoState_Scanline1::GBVideoState_Scanline1(GBVideo* context) :
    IGBVideoState(context)
{

}

void GBVideoState_Scanline1::Tick()
{
    if (m_Context->PerformCycle() == 80)
    {
        m_Context->SetState(new GBVideoState_Scanline2(m_Context));
    }
}
