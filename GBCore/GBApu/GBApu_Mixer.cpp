#include "GBBus.h"
#include "GBApu_Mixer.h"
#include "GBApu_ChannelBase.h"

GBApu_Mixer::GBApu_Mixer(GBApu_ChannelBase* (&channels)[AUDIO_CHANNELS_NUM]) :
	m_Channels(channels)
{
	Reset();
}

void GBApu_Mixer::Reset()
{
	m_NR50 = 0;
	m_NR51 = 0;
    m_SampleR = 0;
    m_SampleR = 0;
}

quint8 GBApu_Mixer::GetVolume(bool isRight)
{
	quint8 volume = 0;
	if (isRight)
	{
		volume = m_NR50 & 0x07;
	}
	else
	{
		volume = (m_NR50 & 0x70) >> 4;
	}
	return volume + 1;
}

quint8 GBApu_Mixer::ComputeSample(bool isRight)
{
    quint8 sample = 0;
	quint8 channelEnableMask = isRight ? 0x01 : 0x10;
	for (int ch = 0; ch < AUDIO_CHANNELS_NUM; ch++)
	{
		if (IsChannelEnabled(channelEnableMask))
		{
			sample += m_Channels[ch]->GetSample();
		}
		channelEnableMask <<= 1;
	}
	sample *= GetVolume(isRight);
	return sample;
}

void GBApu_Mixer::Tick()
{
    m_SampleR = ComputeSample(true);
    m_SampleL = ComputeSample(false);
}

void GBApu_Mixer::ReadRegister(GBBus *bus)
{
	switch (bus->GetAddress())
	{
		case AUDIO_NR50_ADDRESS:
			bus->SetData(m_NR50);
			break;
		case AUDIO_NR51_ADDRESS:
			bus->SetData(m_NR51);
			break;
		default:
			return;
	}
	bus->ReadReqAck();
}

void GBApu_Mixer::WriteRegister(GBBus *bus)
{
	switch (bus->GetAddress())
	{
		case AUDIO_NR50_ADDRESS:
			m_NR50 = bus->GetData();
			break;
		case AUDIO_NR51_ADDRESS:
			m_NR51 = bus->GetData();
			break;
		default:
			return;
	}
	bus->WriteReqAck();
}
