#include "IGBVideoStateContext.h"
#include "GBVideoState_Scanline2.h"
#include "GBVideoState_HBlank.h"
#include "GBBus.h"

GBVideoState_Scanline2::GBVideoState_Scanline2(IGBVideoStateContext* context) :
    IGBVideoState(context)
{
    m_Count = -6; //first 6 cycles are dummy cycles!
    m_PixelCount = 0;
    m_BaseBackgroundTileMapAddress = 0x9800;
    m_BaseBackgroundTileMapAddress |= m_Context->GetBackgroundTileMap() << 11;
    m_BaseBackgroundTileMapAddress |= ((m_Context->GetYLineCount() + m_Context->GetYScroll()) & 0xF8) << 2;
    m_XScroll = m_Context->GetXScroll() >> 3;
}

void GBVideoState_Scanline2::Tick(GBBus* bus)
{
    switch (m_Count % 8)
    {
    case -6:
    case 0:
        //build the address for the first tyle byte
        bus->SetAddress(GetBackgroundTileAddress());
        bus->RequestRead();
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
