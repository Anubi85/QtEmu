#include "GBVideo.h"
#include "GBVideoState_Suspended.h"
#include "GBVideoState_Scanline1.h"

GBVideoState_Suspended::GBVideoState_Suspended(GBVideo* context) :
    IGBVideoState(context)
{

}

void GBVideoState_Suspended::Tick(GBBus* bus)
{
    if (m_Context->IsDisplayEnabled())
    {
        m_Context->SetState(new GBVideoState_Scanline1(m_Context));
    }
}
