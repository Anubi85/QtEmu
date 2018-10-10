#include <QThread>
#include "GBVideo.h"
#include "GBBus.h"
#include "GBUtils.h"

GBVideo::GBVideo() :
    m_FrameSemaphore()
{
    Reset();
}

GBVideo::~GBVideo()
{
    if (m_FrameSemaphore.available() == 0)
    {
        m_FrameSemaphore.release();
        //give time to release the semaphore before destroy it
        QThread::usleep(100);
    }
}

void GBVideo::Reset()
{
    GBComponent::Reset();
    m_Cycles = 0;
    memset(m_VideoRAM, 0, VIDEO_RAM_SIZE);
    memset(m_Registers, 0, VIDEO_REG_SIZE);
    if (m_FrameSemaphore.available() != 0)
    {
        m_FrameSemaphore.acquire();
    }
    memset(m_ScreenBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT);
}

inline quint16 GBVideo::GetModeCycles()
{
    switch (GetVideoMode())
    {
    case VideoMode::HBLANK:
        return 204;
    case VideoMode::VBLANK:
        return 456;
    case VideoMode::SCANLINE1:
        return 80;
    case VideoMode::SCANLINE2:
        return 172;
    }
}

void GBVideo::Tick(GBBus* bus)
{
    //update video mode
    if (IsDisplayEnabled() && (++m_Cycles > GetModeCycles()))
    {
        switch (GetVideoMode())
        {
        case VideoMode::SCANLINE1:
            SetVideoMode(VideoMode::SCANLINE2);
            break;
        case VideoMode::SCANLINE2:
            SetVideoMode(VideoMode::HBLANK);
            break;
        case VideoMode::HBLANK:
            IncreaseYLineCount();
            SetVideoMode(m_Registers[*VideoRegister::LY] < VIDEO_MAX_HBLANK ? VideoMode::SCANLINE1 : VideoMode::VBLANK);
            break;
        case VideoMode::VBLANK:
            IncreaseYLineCount();
            if (m_Registers[*VideoRegister::LY] == 0)
            {
                SetVideoMode(VideoMode::SCANLINE2);
            }
            break;
        }
        m_Cycles = 0;
    }
    //check if a read request is pending and address is in range
    if (bus->IsReadReqPending())
    {
        if (IsAddressInVideoRAM(bus->GetAddress()) && (GetVideoMode() != VideoMode::SCANLINE2 || !IsDisplayEnabled()))
        {
            bus->SetData(m_VideoRAM[bus->GetAddress() - VIDEO_RAM_ADDRESS_OFFSET]);
            bus->ReadReqAck();
        }
        if (IsAddressInVideoReg(bus->GetAddress()))
        {
            switch (static_cast<VideoRegister>(bus->GetAddress() - VIDEO_REG_ADDRESS_OFFSET))
            {
            case VideoRegister::LCDC:
                bus->SetData(m_Registers[*VideoRegister::LCDC]);
                bus->ReadReqAck();
                break;
            case VideoRegister::STAT:
                bus->SetData(m_Registers[*VideoRegister::STAT]);
                bus->ReadReqAck();
                break;
            case VideoRegister::SCY:
                bus->SetData(m_Registers[*VideoRegister::SCY]);
                bus->ReadReqAck();
                break;
            case VideoRegister::LY:
                bus->SetData(m_Registers[*VideoRegister::LY]);
                bus->ReadReqAck();
                break;
            case VideoRegister::BGP:
                bus->SetData(m_Registers[*VideoRegister::BGP]);
                bus->ReadReqAck();
                break;
            }
        }
    }
    //check if a write request is pending and address is in range
    if (bus->IsWriteReqPending())
    {
        if (IsAddressInVideoRAM(bus->GetAddress()) && (GetVideoMode() != VideoMode::SCANLINE2 || !IsDisplayEnabled()))
        {
            m_VideoRAM[bus->GetAddress() - VIDEO_RAM_ADDRESS_OFFSET] = bus->GetData();
            bus->WriteReqAck();
        }
        if (IsAddressInVideoReg(bus->GetAddress()))
        {
            switch (static_cast<VideoRegister>(bus->GetAddress() - VIDEO_REG_ADDRESS_OFFSET))
            {
            case VideoRegister::LCDC:
                if ((((bus->GetData() ^ m_Registers[*VideoRegister::LCDC]) & 0x80) != 0) && !IsDisplayEnabled())
                {
                    //enable bit changed and the display was disabled
                    m_Cycles = 0;
                    SetVideoMode(VideoMode::SCANLINE1);
                }
                m_Registers[*VideoRegister::LCDC] = bus->GetData();
                bus->WriteReqAck();
                break;
            case VideoRegister::STAT:
                m_Registers[*VideoRegister::STAT] = (m_Registers[*VideoRegister::STAT] & 0x03) | (bus->GetData() & 0xFC);
                bus->WriteReqAck();
                break;
            case VideoRegister::SCY:
                m_Registers[*VideoRegister::SCY] = bus->GetData();
                bus->WriteReqAck();
                break;
            case VideoRegister::BGP:
                m_Registers[*VideoRegister::BGP] = bus->GetData();
                bus->WriteReqAck();
                break;
            case VideoRegister::LY:
                //read only registers
                bus->WriteReqAck();
                break;
            }
        }
    }
}

quint32* GBVideo::GetFrame()
{
    m_FrameSemaphore.acquire();
    return m_ScreenBuffer;
}
