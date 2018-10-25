#include "GBAudioChannel_Square.h"

GBAudioChannel_Square::GBAudioChannel_Square(quint16 addressOffset) :
    GBAudioChannelBase(addressOffset)
{
    Reset();
}

void GBAudioChannel_Square::Reset()
{
    GBAudioChannelBase::Reset();
    m_DutyCicle = 0;
    m_DutyStepCount = 0;
    m_LengthCount = 0;
    m_Volume = 0;
    m_CurrentVolume = 0;
    m_EnvelopeAddMode = false;
    m_EnvelopCompleted = true;
    m_Period = 0;
    m_PeriodCounter = 0;
}

void GBAudioChannel_Square::WriteNRx1(quint8 value)
{
    m_DutyCicle = (value & 0xC0) >> 6;
    m_LengthCount = value & 0x3F;
}

void GBAudioChannel_Square::WriteNRx2(quint8 value)
{
    m_Volume = (value & 0xF0) >> 4;
    m_EnvelopeAddMode = (value & 0x08) != 0;
    m_Period = value & 0x07;
}

void GBAudioChannel_Square::WriteNRx3(quint8 value)
{
    m_Frequency = (m_Frequency & 0xFF00) | value;
}

void GBAudioChannel_Square::WriteNRx4(quint8 value)
{
    m_Frequency = (m_Frequency & 0x00FF) | static_cast<quint16>((value & 0x07) << 8);
    m_LengthCounterEnabled = (value & 0x40) != 0;
    m_Enabled = (value & 0x80) != 0;
    if (m_Enabled)
    {
        m_FrequencyCounter = m_Frequency;
        m_CurrentVolume = m_Volume;
        m_PeriodCounter = m_Period;
        m_DutyStepCount = 0;
    }
}

void GBAudioChannel_Square::ProcessModules()
{
    //update base sample based on channel frequency
    if (++m_FrequencyCounter == m_Frequency)
    {
        m_FrequencyCounter = m_Frequency;
        m_BaseAudioSample = s_DutyCicleSamples[m_DutyCicle][m_DutyStepCount++ % DUTY_CICLES_VALUES_NUM];
    }
    //check if length counter shall disable the output
    if ((m_AudioCycles & 0x1) == 0)
    {
        if (!m_Enabled)
        {
            m_BaseAudioSample = 0;
        }
        else
        {
            m_Enabled = m_LengthCounterEnabled ? --m_LengthCount == 0 : true;
        }
    }
    //handle sample the volume
    if (m_AudioCycles == 0x7)
    {
        if (!m_EnvelopCompleted && (m_PeriodCounter-- == 0))
        {
            m_PeriodCounter = m_Period;
            m_CurrentVolume += m_EnvelopeAddMode ? 1 : -1;
            if ((m_CurrentVolume == 0xF) || (m_CurrentVolume == 0))
            {
                m_EnvelopCompleted = true;
            }
        }
        m_Output = m_BaseAudioSample * m_CurrentVolume;
    }
}
