#include "GBAudioModule_SquareWaveGenerator.h"

GBAudioModule_SquareWaveGenerator::GBAudioModule_SquareWaveGenerator(quint8* registers) :
    IGBAudioModule(registers)
{
    Reset();
}

void GBAudioModule_SquareWaveGenerator::Reset()
{
    IGBAudioModule::Reset();
    m_SampleIdx = 0;
    m_Counter = 0;
    m_Enabled = true; //always enabled
}

void GBAudioModule_SquareWaveGenerator::Trigger()
{
    if ((m_Registers[AUDIO_CHANNEL_NR4_IDX] & 0x80) != 0)
    {
        m_SampleIdx = 0;
        m_Counter = GetCounterValue();
    }
}

void GBAudioModule_SquareWaveGenerator::Tick()
{
    if ((GetFrequency() == 0) || (--m_Counter == 0))
    {
        m_Counter = GetCounterValue();
        m_Sample = s_DutyCycles[GetDutyCicle()][m_SampleIdx];
        ++m_SampleIdx &= 0x07;
    }
}
