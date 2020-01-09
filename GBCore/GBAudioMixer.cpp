#include "GBAudioMixer.h"

GBAudioMixer::GBAudioMixer(quint8* switches, quint8* volumes)
{
	m_Switches = switches;
	m_Volumes = volumes;
	m_RightSample = 0;
	m_LeftSample = 0;
}

quint8 GBAudioMixer::GetVolume(bool isRight)
{
	if (isRight)
	{
		return (*m_Volumes & 0x07);
	}
	else
	{
		return (*m_Volumes & 0x70) >> 4;
	}
}

void GBAudioMixer::ComputeSample(bool isRight, qreal sample1, qreal sample2, qreal sample3, qreal sample4)
{
	quint8 mask = isRight ? 0x01 : 0x10;
	qreal sample = 0.0;
	qreal samples[SAMPLES_NUM] = { sample1, sample2, sample3, sample4 };
	for (int i = 0; i < SAMPLES_NUM; i++)
	{
		if (IsChannelEnabled(mask))
		{
			sample += samples[i];
		}
		mask <<= 1;
	}
	sample *= GetVolume(isRight);
	isRight ? (m_RightSample = sample) : (m_LeftSample = sample);
}

void GBAudioMixer::Tick(qreal sample1, qreal sample2, qreal sample3, qreal sample4, quint8 masterVolume)
{
	ComputeSample(true, sample1, sample2, sample3, sample4);
	ComputeSample(false, sample1, sample2, sample3, sample4);
	m_RightSample *= masterVolume;
	m_LeftSample *= masterVolume;
}
