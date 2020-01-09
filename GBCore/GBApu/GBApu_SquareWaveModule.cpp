#include "GBApu_SquareWaveModule.h"

GBApu_SquareWaveModule::GBApu_SquareWaveModule(quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]) :
	GBApu_ChannelModuleBase(registers)
{
}

void GBApu_SquareWaveModule::Reset()
{
	GBApu_ChannelModuleBase::Reset();
	m_SampleIdx = 0;
	m_DutyIdx = 0;
	m_FrequencyCounter = GetFrequencyCount();
}

quint16 GBApu_SquareWaveModule::GetFrequencyCount()
{
	quint16 frequency = m_Registers[AUDIO_CHANNEL_NRX3_ADDRESS];
	frequency |= (m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] & 0x7) << 8;
	return (2048 - frequency) * 4;
}

void GBApu_SquareWaveModule::Trigger()
{
	m_SampleIdx = 0;
	m_DutyIdx = GetDutyCycle();
	m_FrequencyCounter = GetFrequencyCount();
}

void GBApu_SquareWaveModule::Tick(bool doAction, quint8 *sample)
{
	Q_UNUSED(doAction)
	if (--m_FrequencyCounter == 0)
	{
		m_FrequencyCounter = GetFrequencyCount();
		if (++m_SampleIdx == 0x08)
		{
			m_DutyIdx = GetDutyCycle();
			m_SampleIdx = 0;
		}
	}
	*sample = s_DutyCycles[m_DutyIdx][m_SampleIdx];
}
