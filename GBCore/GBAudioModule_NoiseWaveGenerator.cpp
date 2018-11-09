#include "GBAudioModule_NoiseWaveGenerator.h"

GBAudioModule_NoiseWaveGenerator::GBAudioModule_NoiseWaveGenerator(quint8* registers) :
    IGBAudioModule(registers)
{
    Reset();
}

void GBAudioModule_NoiseWaveGenerator::Reset()
{
    IGBAudioModule::Reset();
    m_Counter = 0;
    m_LFSR = 0;
}

void GBAudioModule_NoiseWaveGenerator::UpdateLFSR()
{
    bool newBit = s_LFSRNewBitCalculator[m_LFSR & 0x0003];
    m_LFSR >>= 1;
    m_LFSR &= IsLargeWidthMode() ? 0x3FFF : 0x3FBF;
    if (newBit)
    {
        m_LFSR |= IsLargeWidthMode() ? 0x4000 : 0x4040;
    }
}

quint16 GBAudioModule_NoiseWaveGenerator::GetFrequency()
{
    quint16 counter = GetFrequencyDivider();
    counter = counter != 0 ? counter * 2 : 1;
    counter <<= GetFrequencyShift();
    return counter * 8;
}

void GBAudioModule_NoiseWaveGenerator::Tick()
{
    if (--m_Counter == 0)
    {
        m_Counter = GetFrequency();
        UpdateLFSR();
        m_Sample = m_LFSR & 0x0001;
    }
}
