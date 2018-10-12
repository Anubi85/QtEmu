#include "GBVideo.h"
#include "GBVideoState_Scanline2.h"
#include "GBVideoState_HBlank.h"

GBVideoState_Scanline2::GBVideoState_Scanline2(GBVideo* context) :
    IGBVideoState(context)
{
    m_Count = -6; //first 6 cycles are dummy cycles!
    m_PixelCount = 0;
}

void GBVideoState_Scanline2::Tick(GBBus* bus)
{
    switch (m_Count % 8)
    {
    case -6:
    case 0:
        //put read request to buffer
        break;
    case -5:
    case 1:
        //read from buffer
        break;
    case -4:
    case 2:
        //put read request to buffer
        break;
    case -3:
    case 3:
        //read from buffer
        break;
    case -2:
    case 4:
        //put read request to buffer
        break;
    case -1:
    case 5:
        //read from buffer
        break;
    case 6:
        //dummy cycle, not miplemented yet
        break;
    case 7:
        //dummy cycle, not miplemented yet
        m_PixelCount++;
        break;
    }
    m_Count++;
    if (m_PixelCount == SCREEN_WIDTH)
    {
        m_Context->SetState(new GBVideoState_HBlank(m_Context));
    }
}
