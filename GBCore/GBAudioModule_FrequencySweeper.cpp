#include "GBAudioModule_FrequencySweeper.h"

GBAudioModule_FrequencySweeper::GBAudioModule_FrequencySweeper(quint8* registers) :
    IGBAudioModule(registers)
{
}

void GBAudioModule_FrequencySweeper::Reset()
{
    IGBAudioModule::Reset();
    m_PeriodCounter = 0;
}

void GBAudioModule_FrequencySweeper::Tick()
{
    quint8 shift = GetShift(m_Registers[AUDIO_CHANNEL_NR0_IDX]);
    quint8 period = GetPeriod(m_Registers[AUDIO_CHANNEL_NR0_IDX]);
    bool shallIncrease = ShallIncrease(m_Registers[AUDIO_CHANNEL_NR0_IDX]);
    quint16 frequency = static_cast<quint16>(((m_Registers[AUDIO_CHANNEL_NR4_IDX] & 0x03) << 8) | m_Registers[AUDIO_CHANNEL_NR3_IDX]);
    if ((shift != 0) && ((period == 0) || (--m_PeriodCounter == 0)))
    {
        m_PeriodCounter = period;
        quint16 newFrequency = frequency + static_cast<quint16>((shallIncrease ? 1 : -1) * (frequency >> period));
        if (newFrequency >= 0x0800)
        {
            m_Registers[AUDIO_CHANNEL_NR3_IDX] |= 0xFF;
            m_Registers[AUDIO_CHANNEL_NR4_IDX] |= 0x07;
            m_Sample = 0;
        }
        else
        {
            m_Registers[AUDIO_CHANNEL_NR3_IDX] = newFrequency & 0xFF;
            m_Registers[AUDIO_CHANNEL_NR4_IDX] &= 0xF8;
            m_Registers[AUDIO_CHANNEL_NR4_IDX] |= (newFrequency >> 8) & 0x03;
            m_Sample = 1;
        }
    }
    else
    {
        m_Sample = 1;
    }
}
