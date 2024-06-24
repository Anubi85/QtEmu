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

GBApu::GBApu() : GBComponent()
{
	m_NR52 = 0;
    m_Channels[0] = new GBApu_SweepSquareChannel(m_NR52);
    m_Channels[1] = new GBApu_SquareChannel(m_NR52);
    m_Channels[2] = new GBApu_WaveChannel(m_NR52, m_SamplesRam);
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
    m_SamplesRam[0x0] = 0x84;
    m_SamplesRam[0x1] = 0x40;
    m_SamplesRam[0x2] = 0x43;
    m_SamplesRam[0x3] = 0xAA;
    m_SamplesRam[0x4] = 0x2D;
    m_SamplesRam[0x5] = 0x78;
    m_SamplesRam[0x6] = 0x92;
    m_SamplesRam[0x7] = 0x3C;
    m_SamplesRam[0x8] = 0x60;
    m_SamplesRam[0x9] = 0x59;
    m_SamplesRam[0xA] = 0x59;
    m_SamplesRam[0xB] = 0xB0;
    m_SamplesRam[0xC] = 0x34;
    m_SamplesRam[0xD] = 0xB8;
    m_SamplesRam[0xE] = 0x2E;
    m_SamplesRam[0xF] = 0xDA;
}

void GBApu::ReadRegister(IGBBus* bus)
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
			case NR52_REGISTER:
				bus->SetData(m_NR52 | 0x70);
				break;
			default:
				bus->SetData(0xFF);
		}
		bus->ReadReqAck();
	}
}

void GBApu::WriteRegister(IGBBus* bus)
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
			case NR52_REGISTER:
				m_NR52 &= 0x7F;
                m_NR52 |= (bus->GetData() & 0x80);
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

void GBApu::Tick(GBBus* bus)
{
	if (IsAddressInAudioRam(bus->MainBus()->GetAddress()))
    {
		if (bus->MainBus()->IsReadReqPending())
        {
			bus->MainBus()->SetData(m_SamplesRam[bus->MainBus()->GetLocalAddress(APU_REGISTERS_ADDRESS)]);
			bus->MainBus()->ReadReqAck();
        }
		if (bus->MainBus()->IsWriteReqPending())
        {
			m_SamplesRam[bus->MainBus()->GetLocalAddress(APU_RAM_ADDRESS)] = bus->MainBus()->GetData();
			bus->MainBus()->WriteReqAck();
        }
    }
	if (IsAddressInAudioReg(bus->MainBus()->GetAddress()))
    {
		if (bus->MainBus()->IsReadReqPending())
        {
			ReadRegister(bus->MainBus());
        }
		if (bus->MainBus()->IsWriteReqPending())
        {
			WriteRegister(bus->MainBus());
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
