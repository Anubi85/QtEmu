#include "IGBGpuStateContext.h"
#include "GBGpuState_Scanline2.h"
#include "GBBus.h"

void GBGpuState_Scanline2::Reset()
{
	m_FetcherStepCount = -6; //first 6 cycles are dummy cycles!
    m_PixelCount = 0;
	m_AvailablePixels = 0;
	m_FetchWindow = false;
	quint8 yOffBackground = m_Context->GetYLineCount() + m_Context->GetYScroll();
	quint8 yOffWindow = m_Context->GetWindowLineCount();
	m_BaseBackgroundTileMapAddress = 0x9800;
	m_BaseBackgroundTileMapAddress |= m_Context->GetBackgroundTileMap() << 10;
	m_BaseBackgroundTileMapAddress |= (yOffBackground & 0xF8) << 2;
	m_BaseWindowTileMapAddress = 0x9800;
	m_BaseWindowTileMapAddress |= m_Context->GetWindowTileMap() << 10;
	m_BaseWindowTileMapAddress |= yOffWindow << 2;
    m_XScroll = m_Context->GetXScroll() >> 3;
    m_FineXScroll = m_Context->GetXScroll() & 0x07;
	m_FineBackgroundYScroll = static_cast<quint8>((yOffBackground & 0x07) << 1);
	m_FineWindowYScroll = static_cast<quint8>((yOffWindow & 0x07) << 1);
}

quint16 GBGpuState_Scanline2::GetTileDataAddress(quint8 tileID)
{
    quint16 address = 0x8000;
	address |= (!m_Context->GetTileID() & ~((tileID & 0x80) >> 7)) << 12;
    address |= tileID << 4;
	address |= m_FetchWindow ? m_FineWindowYScroll : m_FineBackgroundYScroll;
    return address;
}

void GBGpuState_Scanline2::Tick(GBBus* bus)
{
    m_Context->PerformCycle();
	switch (m_FetcherStepCount)
    {
    case -6:
    case 0:
		//build the address for the tile number
		m_TileMapAddress = (m_FetchWindow ? m_BaseWindowTileMapAddress : m_BaseBackgroundTileMapAddress) | m_XScroll;
        break;
    case -5:
    case 1:
		//read tile
		bus->SetAddress(m_TileMapAddress);
        bus->RequestRead();
        break;
    case -4:
    case 2:
		//build the address for the first tile byte
		bus->SetAddress(GetTileDataAddress(bus->GetData()));
        bus->RequestRead();
        break;
    case -3:
    case 3:
		//read from bus
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
		//read from bus
        m_NewTileByte2 = bus->GetData();
        break;
    case 6:
        //dummy cycle, not implemented yet
        break;
    case 7:
		//update scroll
        m_XScroll = (m_XScroll + 1) & 0x1F;
		//update tile data
		m_TileByte1 = m_NewTileByte1;
		m_TileByte2 = m_NewTileByte2;
		m_AvailablePixels = 8 - m_FineXScroll;
        break;
    }
	if (m_AvailablePixels != 0)
    {
		//write pixel to screen buffer
		if (m_Context->IsBackgroundEnabled())
		{
			m_Context->SetPixel(m_PixelCount, 2 * ((m_TileByte2 & 0x80) >> 7) + ((m_TileByte1 & 0x80) >> 7));
		}
		else
		{
			m_Context->SetPixel(m_PixelCount, 0);
		}
		m_PixelCount++;
		m_AvailablePixels--;
		m_TileByte1 <<= 1;
		m_TileByte2 <<= 1;
		bool newFetchWindow = m_Context->IsWindowEnabled() && m_Context->IsWindowActive() &&
							  (m_FetchWindow ? ((m_PixelCount - m_Context->GetWindowXCoord()) > SCREEN_WIDTH) : (m_PixelCount >= m_Context->GetWindowXCoord()));
		if (newFetchWindow != m_FetchWindow)
		{
			m_FetchWindow = newFetchWindow;
			//reset tile fetching
			m_FetcherStepCount = -1;
			//stop pushing background pixels
			m_AvailablePixels = 0;
		}
    }
    if (m_PixelCount == SCREEN_WIDTH)
    {
        m_Context->SetState(GpuState::HBlank);
    }
	m_FetcherStepCount = (m_FetcherStepCount + 1) % 8;
}
