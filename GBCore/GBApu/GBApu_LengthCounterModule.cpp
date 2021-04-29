#include "GBApu_LengthCounterModule.h"

GBApu_LengthCounterModule::GBApu_LengthCounterModule(quint8 lengthMask, quint8 channelMask, quint8& apuStatus, quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]) :
	GBApu_ChannelModuleBase(registers),
	c_LenghtMask(lengthMask),
	c_ChannelMask(channelMask),
	m_ApuStatus(apuStatus)
{
}

void GBApu_LengthCounterModule::Reset()
{
    m_OldLength = 0;
}

void GBApu_LengthCounterModule::Trigger()
{
	if(GetLenght() == 0)
	{
        m_OldLength = c_LenghtMask;
        m_Counter.Reload(c_LenghtMask);
        m_ApuStatus |= c_ChannelMask;
	}
}

void GBApu_LengthCounterModule::Tick(bool doAction, quint8* sample)
{
    if (IsEnabled() && doAction)
	{
        quint8 length = GetLenght();
        if (m_OldLength != length)
        {
            m_OldLength = length;
            m_Counter.Reload(length);
        }
        m_Counter.Tick();
        if (m_Counter.IsZero())
        {
            m_ApuStatus &= ~c_ChannelMask;
            *sample = 0;
        }
        else
        {
            m_ApuStatus |= c_ChannelMask;
        }
	}
}
