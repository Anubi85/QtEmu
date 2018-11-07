#include "GBAudioModule_LengthCounter.h"

GBAudioModule_LengthCounter::GBAudioModule_LengthCounter(quint8 lengthMask, quint8* registers) :
    IGBAudioModule(registers),
    c_LengthMask(lengthMask)
{
    Reset();
}

bool GBAudioModule_LengthCounter::DecreaseLength()
{
    quint8 length = m_Registers[AUDIO_CHANNEL_NR1_IDX] & c_LengthMask;
    if (length != 0)
    {
        m_Registers[AUDIO_CHANNEL_NR1_IDX] &= !c_LengthMask;
        m_Registers[AUDIO_CHANNEL_NR1_IDX] |= --length;
    }
    return length == 0;
}

void GBAudioModule_LengthCounter::Tick()
{
    m_Sample = (!PerformCheck() | DecreaseLength()) ? 1 : 0;
}
