#include "GBBus.h"
#include "GBApu.h"
#include "GBApu_ChannelBase.h"
#include "GBApu_FrameSequencer.h"
#include "GBApu_SweepSquareChannel.h"
#include "GBApu_Mixer.h"

GBApu::GBApu() :
	GBComponent(),
	m_SamplesRam{ 0x84, 0x40, 0x43, 0xAA, 0x2D, 0x78, 0x92, 0x3C, 0x60, 0x59, 0x59, 0xB0, 0x34, 0xB8, 0x2E, 0xDA }
{
	m_NR52 = 0;
	m_Channels[0] = new GBApu_SweepSquareChannel(m_NR52);
	m_Channels[1] = nullptr;
	m_Channels[2] = nullptr;
	m_Channels[3] = nullptr;
	m_FrameSequencer = new GBApu_FrameSequencer();
	m_Mixer = new GBApu_Mixer(m_Channels);
}

GBApu::~GBApu()
{
	for (int ch = 0; ch < AUDIO_CHANNELS_NUM; ch++)
	{
		delete m_Channels[ch];
	}
	delete m_FrameSequencer;
	delete m_Mixer;
}

void GBApu::ReadSamplesRam(GBBus *bus)
{
	bus->SetData(m_SamplesRam[bus->GetLocalAddress(AUDIO_REG_ADDRESS_OFFSET)]);
	bus->ReadReqAck();
}

void GBApu::WriteSamplesRam(GBBus *bus)
{
	m_SamplesRam[bus->GetLocalAddress(AUDIO_REG_ADDRESS_OFFSET)] = bus->GetData();
	bus->WriteReqAck();
}

void GBApu::ReadRegister(GBBus *bus)
{
	for(int ch = 0; ch < AUDIO_CHANNELS_NUM; ch++)
	{
		m_Channels[ch]->ReadRegister(bus);
	}
	m_Mixer->ReadRegister(bus);
	if (bus->IsReadReqPending())
	{
		switch (bus->GetAddress())
		{
			case AUDIO_NR52_ADDRESS:
				bus->SetData(m_NR52 | 0x70);
				break;
			default:
				bus->SetData(0xFF);
		}
		bus->ReadReqAck();
	}
}

void GBApu::WriteRegister(GBBus *bus)
{
	for (int ch = 0; ch < AUDIO_CHANNELS_NUM; ch++)
	{
		m_Channels[ch]->WriteRegister(bus);
	}
	m_Mixer->WriteRegister(bus);
	if (bus->IsWriteReqPending())
	{
		switch (bus->GetAddress())
		{
			case AUDIO_NR52_ADDRESS:
				m_NR52 &= 0x7F;
				m_NR52 &= bus->GetData() & 0x80;
				if (!IsAudioEnabled())
				{
					Reset();
				}
				break;
			default:
				//do nothing
				break;
		}
		bus->WriteReqAck();
	}
}

void GBApu::Tick(GBBus *bus)
{
	if (IsAddressInAudioRam(bus->GetAddress()))
	{
		if (bus->IsReadReqPending())
		{
			ReadSamplesRam(bus);
		}
		if (bus->IsWriteReqPending())
		{
			WriteSamplesRam(bus);
		}
	}
	if (IsAddressInAudioReg(bus->GetAddress()))
	{
		if (bus->IsReadReqPending())
		{
			ReadRegister(bus);
		}
		if (bus->IsWriteReqPending())
		{
			WriteRegister(bus);
		}
	}
	m_FrameSequencer->Tick();
	for (int ch = 0;  ch < AUDIO_CHANNELS_NUM; ch++)
	{
		m_Channels[ch]->Tick(m_FrameSequencer);
	}
	m_Mixer->Tick(1); //TODO: Proper handling of master volume
	//TODO: Notify new samples
}
