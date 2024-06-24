#include "GBInternalBus.h"
#include "GBApu_Mixer.h"
#include "GBApu_ChannelBase.h"

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

void GBApu_Mixer::ReadRegister(IGBBus* bus)
{
	switch (bus->GetAddress())
	{
		case NR50_REGISTER:
			bus->SetData(m_NR50);
			break;
		case NR51_REGISTER:
			bus->SetData(m_NR51);
			break;
		default:
			return;
	}
	bus->ReadReqAck();
}

void GBApu_Mixer::WriteRegister(IGBBus* bus)
{
	switch (bus->GetAddress())
	{
		case NR50_REGISTER:
			m_NR50 = bus->GetData();
			break;
		case NR51_REGISTER:
			m_NR51 = bus->GetData();
			break;
		default:
			return;
	}
	bus->WriteReqAck();
}
