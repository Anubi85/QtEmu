#include "GBLengthCounter.h"

GBLengthCounter::GBLengthCounter(quint8 lengthMask, quint8* registers) :
    c_LengthMask(lengthMask)
{
    m_Registers = registers;
    Reset();
}

void GBLengthCounter::Reset()
{
    m_IsEnabled = false;
}

bool GBLengthCounter::DecreaseLength()
{
    quint8 length = m_Registers[AUDIO_CHANNEL_NR1_IDX] & c_LengthMask;
    if (length != 0)
    {
        m_Registers[AUDIO_CHANNEL_NR1_IDX] &= !c_LengthMask;
        m_Registers[AUDIO_CHANNEL_NR1_IDX] |= --length;
    }
    return length == 0;
}

void GBLengthCounter::Tick()
{
    m_IsEnabled = !PerformCheck() | DecreaseLength();
}
