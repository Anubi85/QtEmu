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
}

void GBAudioModule_SquareWaveGenerator::Tick()
{
    if ((GetFrequency() == 0) || (--m_Counter == 0))
    {
        m_Counter = (2048 - GetFrequency()) * 4;
        m_Sample = s_DutyCycles[GetDutyCicle()][m_SampleIdx];
        ++m_SampleIdx &= 0x07;
    }
}
