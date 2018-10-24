#include "GBAudioChannel_Square.h"

GBAudioChannel_Square::GBAudioChannel_Square() :
    GBAudioChannelBase(0xFF15)
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
    m_EnvelopeAddMode = false;
    m_Period = 0;
}

void GBAudioChannel_Square::ProcessModules()
{
    quint8 audioSample = 0;
    if (--m_FrequencyTimer == 0)
    {
        m_FrequencyTimer = m_Frequency;
        audioSample = s_DutyCicleSamples[m_DutyCicle][m_DutyStepCount++ % DUTY_CICLES_VALUES_NUM];
    }
    if(m_LengthCounterEnabled)
    {
        m_Enabled = --m_LengthCount == 0;
    }
}
