#include <QThread>
#include <QFile>
#include "GBGpu.h"
#include "GBBus.h"
#include "GBDma.h"
#include "GBUtils.h"
#include "GBGpuState_HBlank.h"
#include "GBGpuState_VBlank.h"
#include "GBGpuState_Scanline1.h"
#include "GBGpuState_Scanline2.h"
#include "GBGpuState_Suspended.h"

GBGpu::GBGpu() :
    m_FrameSemaphore()
{
    m_GpuStates[*GpuState::HBlank] = new GBGpuState_HBlank(this);
    m_GpuStates[*GpuState::VBlank] = new GBGpuState_VBlank(this);
    m_GpuStates[*GpuState::Scanline1] = new GBGpuState_Scanline1(this);
    m_GpuStates[*GpuState::Scanline2] = new GBGpuState_Scanline2(this);
    m_GpuStates[*GpuState::Suspended] = new GBGpuState_Suspended(this);
    m_State = nullptr;
	m_Dma = new GBDma();
	Reset();
}

GBGpu::~GBGpu()
{
    for (int state = 0; state < GPU_STATES_NUM; state++)
    {
        delete m_GpuStates[state];
    }
    //no need to delete m_state because already deleted by the above loop
    if (m_FrameSemaphore.available() == 0)
    {
        m_FrameSemaphore.release();
        //give time to release the semaphore before destroy it
        QThread::usleep(100);
    }
	delete m_Dma;
}

void GBGpu::Reset()
{
    GBComponent::Reset();
    m_Cycles = 0;
	memset(m_VideoRAM, 0, GPU_RAM_SIZE);
	memset(m_Registers, 0, GPU_REGISTERS_SIZE);
	memset(m_VideoOAM, 0, OAM_TOTAL_SIZE);
    if (m_FrameSemaphore.available() != 0)
    {
        m_FrameSemaphore.acquire();
    }
    memset(m_ScreenBuffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(quint32));
    m_State = m_GpuStates[*GpuState::Suspended];
    m_State->Reset();
	m_Dma->Reset();
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

void GBGpu::ReadVideoRAM(IGBBus* bus, bool modeOverride)
{
    //check if a read request is pending and address is in range
	if (bus->IsReadReqPending() && IsAddressInVideoRAM(bus->GetAddress()))
    {
        if ((GetVideoMode() != GpuState::Scanline2) || modeOverride)
        {
			bus->SetData(m_VideoRAM[bus->GetLocalAddress(GPU_RAM_ADDRESS)]);
        }
        else
        {
			bus->SetData(0xFF);
        }
		bus->ReadReqAck();
    }
}

void GBGpu::WriteVideoRAM(IGBBus* bus)
{
    //check if a write request is pending and address is in range
    if (bus->IsWriteReqPending() && IsAddressInVideoRAM(bus->GetAddress()))
    {
		if (GetVideoMode() != GpuState::Scanline2)
        {
			m_VideoRAM[bus->GetLocalAddress(GPU_RAM_ADDRESS)] = bus->GetData();
        }
        bus->WriteReqAck();
    }
}

void GBGpu::ReadVideoRegister(IGBBus* bus)
{
    //check if a read request is pending and address is in range
    if (bus->IsReadReqPending() && IsAddressInVideoReg(bus->GetAddress()))
    {
		switch (bus->GetAddress())
        {
		case LCDC_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)]);
            bus->ReadReqAck();
            break;
		case STAT_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)]);
            bus->ReadReqAck();
            break;
		case SCY_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)]);
            bus->ReadReqAck();
            break;
		case SCX_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)]);
            bus->ReadReqAck();
            break;
		case LY_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)]);
            bus->ReadReqAck();
            break;
		case DMA_REGISTER:
			bus->SetAddress(0xFF); //Register is read-only
			bus->ReadReqAck();
			break;
		case BGP_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)]);
            bus->ReadReqAck();
            break;
		case OBP0_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)]);
			bus->ReadReqAck();
			break;
		case OBP1_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)]);
			bus->ReadReqAck();
			break;
		case WX_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)]);
			bus->ReadReqAck();
			break;
		case WY_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)]);
			bus->ReadReqAck();
			break;
        }
    }
}

void GBGpu::WriteVideoRegister(IGBBus* bus)
{
    //check if a write request is pending and address is in range
    if (bus->IsWriteReqPending() && IsAddressInVideoReg(bus->GetAddress()))
    {
		switch (bus->GetAddress())
        {
		case LCDC_REGISTER:
			m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)] = bus->GetData();
            bus->WriteReqAck();
            break;
		case STAT_REGISTER:
			m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)] = (m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)] & 0x03) | (bus->GetData() & 0xFC);
            bus->WriteReqAck();
            break;
		case SCY_REGISTER:
			m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)] = bus->GetData();
            bus->WriteReqAck();
            break;
		case SCX_REGISTER:
			m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)] = bus->GetData();
            bus->WriteReqAck();
            break;
		case BGP_REGISTER:
			m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)] = bus->GetData();
            bus->WriteReqAck();
            break;
		case OBP0_REGISTER:
			m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)] = bus->GetData();
			bus->WriteReqAck();
			break;
		case OBP1_REGISTER:
			m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)] = bus->GetData();
			bus->WriteReqAck();
			break;
		case LY_REGISTER:
            //read only registers
            bus->WriteReqAck();
            break;
		case DMA_REGISTER:
			m_Dma->Start(bus->GetData());
			bus->WriteReqAck();
			break;
		case WY_REGISTER:
			m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)] = bus->GetData();
			bus->WriteReqAck();
			break;
		case WX_REGISTER:
			m_Registers[bus->GetLocalAddress(GPU_REGISTERS_ADDRESS)] = bus->GetData();
			bus->WriteReqAck();
			break;
        }
    }
}

void GBGpu::ReadVideoOAM(IGBBus* bus, bool modeOverride)
{
	//check if a read request is pending and address is in range
	if (bus->IsReadReqPending() && IsAddressInVideoOAM(bus->GetAddress()))
	{
		GpuState videoMode = GetVideoMode();
		if (((videoMode != GpuState::Scanline1) && (videoMode != GpuState::Scanline2)) || modeOverride)
		{
			quint16 oamAddress = bus->GetLocalAddress(OAM_ADDRESS);
			if (oamAddress < OAM_VALID_SIZE)
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

void GBGpu::WriteVideoOAM(IGBBus* bus)
{
	//check if a write request is pending and address is in range
	if (bus->IsWriteReqPending() && IsAddressInVideoOAM(bus->GetAddress()))
	{
		GpuState videoMode = GetVideoMode();
		if ((videoMode != GpuState::Scanline1) && (videoMode != GpuState::Scanline2))
		{
			quint16 oamAddress = bus->GetLocalAddress(OAM_ADDRESS);
			if (oamAddress < OAM_VALID_SIZE)
			{
				m_VideoOAM[oamAddress] = bus->GetData();
			}
		}
		bus->WriteReqAck();
	}
}

void GBGpu::Tick(GBBus* bus)
{
	if (bus->IsDmaActive())
	{
		//read VRAM from DMA bus
		ReadVideoRAM(bus->DmaBus(), false);
		//read OAM from DMA bus
		ReadVideoOAM(bus->DmaBus(), false);
		//write OAM from DMA bus
		WriteVideoOAM(bus->DmaBus());
	}
    //read VRAM from standard bus
	ReadVideoRAM(bus->MainBus(), false);
    //read registers
	ReadVideoRegister(bus->MainBus());
	//read OAM from standard bus
	ReadVideoOAM(bus->MainBus(), false);
    //write VRAM
	WriteVideoRAM(bus->MainBus());
    //write registers
	WriteVideoRegister(bus->MainBus());
	//write OAM from standard bus
	WriteVideoOAM(bus->MainBus());
    //perform state action
	m_State->Tick(bus->GpuBus());
    //read VRAM from internal bus
	ReadVideoRAM(bus->GpuBus(), true);
	//read OAM from internal bus
	ReadVideoOAM(bus->GpuBus(), true);
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
