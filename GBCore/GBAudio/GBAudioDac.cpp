#include "GBAudioDac.h"
#include "GBAudioCommonDefs.h"

GBAudioDac::GBAudioDac(quint8* registers, bool isWaveChannel):
	c_Gain(2.0/15.0),
	c_Offset(-1.0)
{
	m_Registers = registers;
	m_IsWaveChannel = isWaveChannel;
}

bool GBAudioDac::IsEnabled()
{
	if (m_IsWaveChannel)
	{
		return (m_Registers[AUDIO_CHANNEL_NR3_IDX] & 0x80) != 0;
	}
	else
	{
		return (m_Registers[AUDIO_CHANNEL_NR2_IDX] & 0xF8) != 0;
	}
}

qreal GBAudioDac::GetSample(quint8 frequencySample, quint8 waveSample, quint8 lengthSample, quint8 volumeSample)
{
	if (IsEnabled())
	{
		return (frequencySample * waveSample * lengthSample * volumeSample) * c_Gain + c_Offset;
	}
	else
	{
		return 0.0;
	}
}
