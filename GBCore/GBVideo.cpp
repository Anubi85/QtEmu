#include <QThread>
#include "GBVideo.h"
#include "GBBus.h"
#include "GBUtils.h"
#include "GBVideoState_Suspended.h"

GBVideo::GBVideo() :
    m_FrameSemaphore()
{
    m_State = nullptr;
    m_InternalBus = new GBBus();
    Reset();
}

GBVideo::~GBVideo()
{
    delete m_State;
    delete m_InternalBus;
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
    memset(m_ScreenBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(quint32));
    delete m_State;
    m_State = new GBVideoState_Suspended(this);
    m_InternalBus->Clear();
}

void GBVideo::SetState(IGBVideoState* newState)
{
    if (newState->GetStateID() == VideoState::Suspended)
    {
        memset(m_ScreenBuffer, 0xFF, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(quint32));
        m_FrameSemaphore.release();
    }
    delete m_State;
    m_State = newState;
}

void GBVideo::ReadVideoRAM(GBBus* bus, bool modeOverride)
{
    //check if a read request is pending and address is in range
    if (bus->IsReadReqPending() && IsAddressInVideoRAM(bus->GetAddress()))
    {
        if ((GetVideoMode() != VideoState::Scanline2) || modeOverride)
        {
            bus->SetData(m_VideoRAM[bus->GetAddress() - VIDEO_RAM_ADDRESS_OFFSET]);
        }
        else
        {
            bus->SetData(0xFF);
        }
        bus->ReadReqAck();
    }
}

void GBVideo::WriteVideoRAM(GBBus* bus)
{
    //check if a write request is pending and address is in range
    if (bus->IsWriteReqPending() && IsAddressInVideoRAM(bus->GetAddress()))
    {
        if (GetVideoMode() != VideoState::Scanline2)
        {
            m_VideoRAM[bus->GetAddress() - VIDEO_RAM_ADDRESS_OFFSET] = bus->GetData();
        }
        bus->WriteReqAck();
    }
}

void GBVideo::ReadVideoRegister(GBBus* bus)
{
    //check if a read request is pending and address is in range
    if (bus->IsReadReqPending() && IsAddressInVideoReg(bus->GetAddress()))
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
        case VideoRegister::SCX:
            bus->SetData(m_Registers[*VideoRegister::SCX]);
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

void GBVideo::WriteVideoRegister(GBBus* bus)
{
    //check if a write request is pending and address is in range
    if (bus->IsWriteReqPending() && IsAddressInVideoReg(bus->GetAddress()))
    {
        switch (static_cast<VideoRegister>(bus->GetAddress() - VIDEO_REG_ADDRESS_OFFSET))
        {
        case VideoRegister::LCDC:
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
        case VideoRegister::SCX:
            m_Registers[*VideoRegister::SCX] = bus->GetData();
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

void GBVideo::Tick(GBBus* bus)
{
    //read VRAM from standard bus
    ReadVideoRAM(bus, false);
    //read registers
    ReadVideoRegister(bus);
    //write VRAM
    WriteVideoRAM(bus);
    //write registers
    WriteVideoRegister(bus);
    //perform state action
    m_State->Tick(m_InternalBus);
    //read VRAM from internal bus
    ReadVideoRAM(m_InternalBus, true);
}

quint32* GBVideo::GetFrame()
{
    m_FrameSemaphore.acquire();
    return m_ScreenBuffer;
}
