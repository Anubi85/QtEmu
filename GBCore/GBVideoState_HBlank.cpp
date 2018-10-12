#include "GBVideo.h"
#include "GBVideoState_HBlank.h"
#include "GBVideoState_Scanline1.h"
#include "GBVideoState_VBlank.h"

GBVideoState_HBlank::GBVideoState_HBlank(GBVideo* context) :
    IGBVideoState(context)
{

}

void GBVideoState_HBlank::Tick(GBBus* bus)
{
    if ((m_Context->PerformCycle() % 456) == 0)
    {
        m_Context->ResetCycles();
        m_Context->IncreaseYLineCount();
        if (m_Context->GetYLineCount() == VIDEO_MAX_HBLANK)
        {
            m_Context->SetState(new GBVideoState_VBlank(m_Context));
        }
        else
        {
            m_Context->SetState(new GBVideoState_Scanline1(m_Context));
        }
    }
}
