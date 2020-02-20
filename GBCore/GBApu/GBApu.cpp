#include <QThread>
#include "GBBus.h"
#include "GBApu.h"
#include "GBApu_ChannelBase.h"
#include "GBApu_FrameSequencer.h"
#include "GBApu_SweepSquareChannel.h"
#include "GBApu_SquareChannel.h"
#include "GBApu_WaveChannel.h"
#include "GBApu_NoiseChannel.h"
#include "GBApu_Mixer.h"

GBApu::GBApu() :
	GBComponent(),
	m_SamplesRam{ 0x84, 0x40, 0x43, 0xAA, 0x2D, 0x78, 0x92, 0x3C, 0x60, 0x59, 0x59, 0xB0, 0x34, 0xB8, 0x2E, 0xDA }
{
	m_NR52 = 0;
	m_Channels[0] = new GBApu_SweepSquareChannel(m_NR52);
    m_Channels[1] = new GBApu_SquareChannel(m_NR52);
    m_Channels[2] = new GBApu_WaveChannel(m_NR52);
    m_Channels[3] = new GBApu_NoiseChannel(m_NR52);
	m_FrameSequencer = new GBApu_FrameSequencer();
	m_Mixer = new GBApu_Mixer(m_Channels);
    Reset();
}

GBApu::~GBApu()
{
	for (int ch = 0; ch < AUDIO_CHANNELS_NUM; ch++)
	{
		delete m_Channels[ch];
	}
	delete m_FrameSequencer;
	delete m_Mixer;
    if (m_SamplesSemaphore.available() == 0)
    {
        m_SamplesSemaphore.release();
        //give time to release the semaphore before destroy it
        QThread::usleep(100);
    }
}

void GBApu::Reset()
{
    m_CurrentBuffer = false;
    m_SamplesCounter = 0;
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
    m_Mixer->Tick();
    AddSamplesToBuffer(m_Mixer->GetSampleL(), m_Mixer->GetSampleR());
}

void GBApu::AddSamplesToBuffer(quint8 lSample, quint8 rSample)
{
    m_SamplesBuffer[m_CurrentBuffer][m_SamplesCounter++] = lSample;
    m_SamplesBuffer[m_CurrentBuffer][m_SamplesCounter++] = rSample;
    if (m_SamplesCounter >= SAMPLES_BUFFER_SIZE)
    {
        m_SamplesCounter = 0;
        m_CurrentBuffer = !m_CurrentBuffer;
        m_SamplesSemaphore.release();
    }
}

quint8* GBApu::GetSamples()
{
    m_SamplesSemaphore.acquire();
    return m_SamplesBuffer[!m_CurrentBuffer];
}
