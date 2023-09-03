#include <QThread>
#include "GBGpu.h"
#include "GBBus.h"
#include "GBUtils.h"
#include "GBGpuState_HBlank.h"
#include "GBGpuState_VBlank.h"
#include "GBGpuState_Scanline1.h"
#include "GBGpuState_Scanline2.h"
#include "GBGpuState_Suspended.h"
#include <QFile>

GBGpu::GBGpu() :
    m_FrameSemaphore()
{
    m_GpuStates[*GpuState::HBlank] = new GBGpuState_HBlank(this);
    m_GpuStates[*GpuState::VBlank] = new GBGpuState_VBlank(this);
    m_GpuStates[*GpuState::Scanline1] = new GBGpuState_Scanline1(this);
    m_GpuStates[*GpuState::Scanline2] = new GBGpuState_Scanline2(this);
    m_GpuStates[*GpuState::Suspended] = new GBGpuState_Suspended(this);
    m_State = nullptr;
    m_InternalBus = new GBBus();
    Reset();
}

GBGpu::~GBGpu()
{
    for (int state = 0; state < GPU_STATES_NUM; state++)
    {
        delete m_GpuStates[state];
    }
    //no need to delete m_state because already deleted by the above loop
    delete m_InternalBus;
    if (m_FrameSemaphore.available() == 0)
    {
        m_FrameSemaphore.release();
        //give time to release the semaphore before destroy it
        QThread::usleep(100);
    }
}

void GBGpu::Reset()
{
    GBComponent::Reset();
    m_Cycles = 0;
    memset(m_VideoRAM, 0, VIDEO_RAM_SIZE);
    memset(m_Registers, 0, VIDEO_REG_SIZE);
	memset(m_VideoOAM, 0, VIDEO_OAM_SIZE);
    if (m_FrameSemaphore.available() != 0)
    {
        m_FrameSemaphore.acquire();
    }
    memset(m_ScreenBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(quint32));
    m_State = m_GpuStates[*GpuState::Suspended];
    m_State->Reset();
    m_InternalBus->Clear();
}

void GBGpu::SetState(GpuState newStateId)
{
    if (newStateId == GpuState::Suspended)
    {
        memset(m_ScreenBuffer, 0xFF, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(quint32));
        m_FrameSemaphore.release();
    }
    m_State = m_GpuStates[*newStateId];
    m_State->Reset();
}

void GBGpu::ReadVideoRAM(GBBus* bus, bool modeOverride)
{
    //check if a read request is pending and address is in range
    if (bus->IsReadReqPending() && IsAddressInVideoRAM(bus->GetAddress()))
    {
        if ((GetVideoMode() != GpuState::Scanline2) || modeOverride)
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

void GBGpu::WriteVideoRAM(GBBus* bus)
{
    //check if a write request is pending and address is in range
    if (bus->IsWriteReqPending() && IsAddressInVideoRAM(bus->GetAddress()))
    {
        if (GetVideoMode() != GpuState::Scanline2)
        {
            m_VideoRAM[bus->GetAddress() - VIDEO_RAM_ADDRESS_OFFSET] = bus->GetData();
        }
        bus->WriteReqAck();
    }
}

void GBGpu::ReadVideoRegister(GBBus* bus)
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
		case VideoRegister::OBP0:
			bus->SetData(m_Registers[*VideoRegister::OBP0]);
			bus->ReadReqAck();
			break;
		case VideoRegister::OBP1:
			bus->SetData(m_Registers[*VideoRegister::OBP1]);
			bus->ReadReqAck();
			break;
        }
    }
}

void GBGpu::WriteVideoRegister(GBBus* bus)
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
		case VideoRegister::OBP0:
			m_Registers[*VideoRegister::OBP0] = bus->GetData();
			bus->WriteReqAck();
			break;
		case VideoRegister::OBP1:
			m_Registers[*VideoRegister::OBP1] = bus->GetData();
			bus->WriteReqAck();
			break;
        case VideoRegister::LY:
            //read only registers
            bus->WriteReqAck();
            break;
        }
    }
}

void GBGpu::ReadVideoOAM(GBBus *bus, bool modeOverride)
{
	//check if a read request is pending and address is in range
	if (bus->IsReadReqPending() && IsAddressInVideoOAM(bus->GetAddress()))
	{
		GpuState videoMode = GetVideoMode();
		if (((videoMode != GpuState::Scanline1) && (videoMode != GpuState::Scanline2)) || modeOverride)
		{
			quint16 oamAddress = bus->GetAddress() - VIDEO_OAM_ADDRESS_OFFSET;
			if (oamAddress < VIDEO_VALID_OAM_SIZE)
			{
				bus->SetData(m_VideoOAM[oamAddress]);
			}
			else
			{
				bus->SetData(0x00);
			}
		}
		else
		{
			bus->SetData(0xFF);
		}
		bus->ReadReqAck();
	}
}

void GBGpu::WriteVideoOAM(GBBus* bus)
{
	//check if a write request is pending and address is in range
	if (bus->IsWriteReqPending() && IsAddressInVideoOAM(bus->GetAddress()))
	{
		GpuState videoMode = GetVideoMode();
		if ((videoMode != GpuState::Scanline1) && (videoMode != GpuState::Scanline2))
		{
			quint16 oamAddress = bus->GetAddress() - VIDEO_OAM_ADDRESS_OFFSET;
			if (oamAddress < VIDEO_VALID_OAM_SIZE)
			{
				m_VideoOAM[oamAddress] = bus->GetData();
			}
		}
		bus->WriteReqAck();
	}
}

void GBGpu::Tick(GBBus* bus, GBInterruptBus* interruptBus)
{
    //read VRAM from standard bus
    ReadVideoRAM(bus, false);
    //read registers
    ReadVideoRegister(bus);
	//read OAM
	ReadVideoOAM(bus, false);
    //write VRAM
    WriteVideoRAM(bus);
    //write registers
    WriteVideoRegister(bus);
	//write OAM
	WriteVideoOAM(bus);
    //perform state action
    m_State->Tick(m_InternalBus);
    //read VRAM from internal bus
    ReadVideoRAM(m_InternalBus, true);
	//read OAM from internal bus
	ReadVideoOAM(m_InternalBus, true);
}

quint32* GBGpu::GetFrame()
{
    m_FrameSemaphore.acquire();
    return m_ScreenBuffer;
}

void GBGpu::SetPixel(quint8 pixelIdx, quint8 pixelValue)
{
    quint8 paletteColor = 0;
    //Get palette color
    switch (pixelValue)
    {
    case 0b00:
        paletteColor = m_Registers[*VideoRegister::BGP] & 0x03;
        break;
    case 0b01:
        paletteColor = (m_Registers[*VideoRegister::BGP] & 0x0C) >> 2;
        break;
    case 0b10:
        paletteColor = (m_Registers[*VideoRegister::BGP] & 0x30) >> 4;
        break;
    case 0b11:
        paletteColor = (m_Registers[*VideoRegister::BGP] & 0xC0) >> 6;
        break;
    }
    m_ScreenBuffer[m_Registers[*VideoRegister::LY] * SCREEN_WIDTH + pixelIdx] = s_Palettes[*Palette::BlueLight][paletteColor];
}
