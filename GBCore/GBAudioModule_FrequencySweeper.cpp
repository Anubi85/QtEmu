#include "GBAudioModule_FrequencySweeper.h"

GBAudioModule_FrequencySweeper::GBAudioModule_FrequencySweeper(quint8* registers) :
    IGBAudioModule(registers)
{
    Reset();
}

void GBAudioModule_FrequencySweeper::Reset()
{
    IGBAudioModule::Reset();
    m_ShadowFrequency = 0;
    m_PeriodCounter = 0;
    m_Sample = 1; //fixed value
}

void GBAudioModule_FrequencySweeper::Trigger()
{
    if ((m_Registers[AUDIO_CHANNEL_NR4_IDX] & 0x80) != 0)
    {
        m_ShadowFrequency = GetFrequency();
        m_PeriodCounter = GetPeriod();
        m_Enabled = (GetPeriod() != 0) || (GetShift() != 0);
        ComputeNewFrequency();
    }
}

void GBAudioModule_FrequencySweeper::ComputeNewFrequency()
{
    if (GetShift() != 0)
    {
        m_ShadowFrequency >>= GetShift();
        m_ShadowFrequency = m_ShadowFrequency + (ShallNegate() ? -m_ShadowFrequency : m_ShadowFrequency);
        m_ShadowFrequency = (m_ShadowFrequency > FREQUENCY_MAX_VALUE) ? FREQUENCY_MAX_VALUE : m_ShadowFrequency;
        m_Enabled = m_ShadowFrequency < FREQUENCY_MAX_VALUE;
    }
}

void GBAudioModule_FrequencySweeper::Tick()
{
    if (m_Enabled && (--m_PeriodCounter == 0))
    {
        m_PeriodCounter = GetPeriod();
        ComputeNewFrequency();
        m_Registers[AUDIO_CHANNEL_NR3_IDX] = m_ShadowFrequency & 0xFF;
        m_Registers[AUDIO_CHANNEL_NR4_IDX] &= 0xF8;
        m_Registers[AUDIO_CHANNEL_NR4_IDX] |= (m_ShadowFrequency >> 8) & 0x03;
    }
}
