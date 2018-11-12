#include "GBAudioModule_LengthCounter.h"

GBAudioModule_LengthCounter::GBAudioModule_LengthCounter(quint8 lengthMask, quint8* registers) :
    IGBAudioModule(registers),
    c_LengthMask(lengthMask)
{
    Reset();
}

void inline GBAudioModule_LengthCounter::SetLength(quint8 value)
{
    m_Registers[AUDIO_CHANNEL_NR1_IDX] &= !c_LengthMask;
    m_Registers[AUDIO_CHANNEL_NR1_IDX] |= value;
}

void GBAudioModule_LengthCounter::DecreaseLength()
{
    quint8 length = GetLenght();
    if (length != 0)
    {
        SetLength(--length);
    }
    m_Enabled = length == 0;
}

void GBAudioModule_LengthCounter::Trigger()
{
    if ((m_Registers[AUDIO_CHANNEL_NR4_IDX] & 0x80) != 0)
    {
        m_Enabled = GetLenght() != 0;
    }
}

void GBAudioModule_LengthCounter::Tick()
{
    if (m_Enabled && PerformCheck())
    {
        DecreaseLength();
    }
}
