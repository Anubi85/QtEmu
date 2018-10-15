#include "IGBVideoStateContext.h"
#include "GBVideoState_VBlank.h"
#include "GBVideoState_Scanline1.h"
#include "GBVideoState_Suspended.h"

GBVideoState_VBlank::GBVideoState_VBlank(IGBVideoStateContext* context) :
    IGBVideoState(context)
{

}

void GBVideoState_VBlank::Tick(GBBus* bus)
{
    if (!m_Context->IsDisplayEnabled())
    {
        m_Context->SetState(new GBVideoState_Suspended(m_Context));
    }
    else if(m_Context->PerformCycle() == 456)
    {
        m_Context->ResetCycles();
        m_Context->IncreaseYLineCount();
        if (m_Context->GetYLineCount() == VIDEO_MAX_Y_LINE_COUNT)
        {
            m_Context->SetState(new GBVideoState_Scanline1(m_Context));
        }
    }
}
