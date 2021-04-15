#include "IGBVideoStateContext.h"
#include "GBVideoState_Scanline2.h"
#include "GBVideoState_HBlank.h"
#include "GBBus.h"

GBVideoState_Scanline2::GBVideoState_Scanline2(IGBVideoStateContext* context) :
    IGBVideoState(context)
{
    m_Count = -6; //first 6 cycles are dummy cycles!
    m_PixelCount = 0;
    quint8 yOff = m_Context->GetYLineCount() + m_Context->GetYScroll();
    m_BaseBackgroundTileMapAddress = 0x9800;
    m_BaseBackgroundTileMapAddress |= m_Context->GetBackgroundTileMap() << 10;
    m_BaseBackgroundTileMapAddress |= (yOff & 0xF8) << 2;
    m_XScroll = m_Context->GetXScroll() >> 3;
    m_FineXScroll = m_Context->GetXScroll() & 0x07;
    m_FineYScroll = yOff & 0x07;
}

quint16 GBVideoState_Scanline2::GetBackgroundTileDataAddress(quint8 tileID)
{
    quint16 address = 0x8000;
    address |= (!m_Context->GetBackgroundTileID() & ~((tileID & 0x80) >> 7)) << 12;
    address |= tileID << 4;
    address |= m_FineYScroll << 1;
    return address;
}

void GBVideoState_Scanline2::Tick(GBBus* bus)
{
    m_Context->PerformCycle();
    switch (m_Count % 8)
    {
    case -6:
    case 0:
        //update tile data
        m_TileByte1 = m_NewTileByte1;
        m_TileByte2 = m_NewTileByte2;
        //build the address for the first tyle byte
        bus->SetAddress(GetBackgroundTileAddress());
        break;
    case -5:
    case 1:
        //read from buffer
        bus->RequestRead();
        break;
    case -4:
    case 2:
        //build the address for the first tile byte
        bus->SetAddress(GetBackgroundTileDataAddress(bus->GetData()));
        bus->RequestRead();
        break;
    case -3:
    case 3:
        //read from buffer
        m_NewTileByte1 = bus->GetData();
        break;
    case -2:
    case 4:
        //build the address for the second tile byte
        bus->SetAddress(bus->GetAddress() + 1);
        bus->RequestRead();
        break;
    case -1:
    case 5:
        //read from buffer
        m_NewTileByte2 = bus->GetData();
        break;
    case 6:
        //dummy cycle, not implemented yet
        break;
    case 7:
        //dummy cycle, not implemented yet
        m_XScroll = (m_XScroll + 1) & 0x1F;
        break;
    }
    if (m_Count++ >= 8) //first read is just discarded!!
    {
        if (m_FineXScroll == 0)
        {
            //write pixel to screen buffer
            m_Context->SetPixel(m_PixelCount++, 2 * ((m_TileByte2 & 0x80) >> 7) + ((m_TileByte1 & 0x80) >> 7));
        }
        else
        {
            m_FineXScroll--;
        }
    }
    m_TileByte1 <<= 1;
    m_TileByte2 <<= 1;
    if (m_PixelCount == SCREEN_WIDTH)
    {
        m_Context->SetState(new GBVideoState_HBlank(m_Context));
    }
}
