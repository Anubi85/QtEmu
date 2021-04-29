#include "GBApu_FrequencySweepModule.h"

GBApu_FrequencySweepModule::GBApu_FrequencySweepModule(quint8 channelMask, quint8& apuStatus, quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]) :
    GBApu_ChannelModuleBase(registers),
    c_ChannelMask(channelMask),
    m_ApuStatus(apuStatus)
{
}

void GBApu_FrequencySweepModule::Reset()
{
    m_ShadowFrequency = 0;
}

void GBApu_FrequencySweepModule::Trigger()
{
    m_ShadowFrequency = GetFrequency();
    quint8 sweepCount = GetSweepCount();
    m_Counter.Reload(sweepCount);
    if (GetShiftValue() != 0)
    {
        quint16 newFrequency = ComputeNewFrequency();
        OverflowCheck(newFrequency);
    }
}

void GBApu_FrequencySweepModule::Tick(bool doAction, quint8 *sample)
{
    Q_UNUSED(sample)
    if (doAction)
    {
        m_Counter.Tick();
        if (m_Counter.IsZero())
        {
            m_Counter.Reload(GetSweepCount());
            quint16 newFrequency = ComputeNewFrequency();
            if (OverflowCheck(newFrequency))
            {
                m_ShadowFrequency = newFrequency;
                m_Registers[AUDIO_CHANNEL_NRX3_ADDRESS] = newFrequency & 0xFF;
                m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] &= 0xF8;
                m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] |= (newFrequency >> 8) & 0x03;
            }
            else
            {
                *sample = 0;
            }
        }
    }
}

quint16 GBApu_FrequencySweepModule::ComputeNewFrequency()
{
    quint32 shift = GetShiftValue();
    if (shift != 0)
    {
        quint16 deltaFrequency = m_ShadowFrequency >> shift;
        if (IsAddMode())
        {
            return m_ShadowFrequency + deltaFrequency;
        }
        else
        {
            return m_ShadowFrequency - deltaFrequency;
        }
    }
    else
    {
        return  m_ShadowFrequency;
    }
}

bool GBApu_FrequencySweepModule::OverflowCheck(quint16 newFrequency)
{
    if (newFrequency > MAX_FREQUENCY)
    {
        m_ApuStatus &= ~c_ChannelMask;
        return false;
    }
    return true;
}
