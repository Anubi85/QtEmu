#include "GBApu_LengthCounterModule.h"

GBApu_LengthCounterModule::GBApu_LengthCounterModule(quint8 lengthMask, quint8 channelMask, quint8& apuStatus, quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]) :
	GBApu_ChannelModuleBase(registers),
	c_LenghtMask(lengthMask),
	c_ChannelMask(channelMask),
	m_ApuStatus(apuStatus)
{

}

void GBApu_LengthCounterModule::SetLenght(quint8 value)
{
	m_Registers[AUDIO_CHANNEL_NRX1_ADDRESS] &= ~c_LenghtMask;
	m_Registers[AUDIO_CHANNEL_NRX1_ADDRESS] |= value;
}

void GBApu_LengthCounterModule::Trigger()
{
	if(GetLenght() == 0)
	{
		SetLenght(c_LenghtMask);
	}
}

void GBApu_LengthCounterModule::Tick(bool doAction, quint8* sample)
{
	if ((m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] & 0x40) != 0 && doAction)
	{
		quint8 length = GetLenght();
		if (length != 0)
		{
			SetLenght(--length);
			m_ApuStatus |= c_ChannelMask;
		}
		else
		{
			m_ApuStatus &= ~c_ChannelMask;
		}
	}
	if ((m_ApuStatus & c_ChannelMask) == 0)
	{
		*sample = 0;
	}
}
