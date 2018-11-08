#include "GBAudioModule_RamWaveGenerator.h"

GBAudioModule_RamWaveGenerator::GBAudioModule_RamWaveGenerator(quint8* registers) :
    IGBAudioModule(registers)
{
    m_SamplesRAM = registers + AUDIO_SAMPLES_OFFSET;
    Reset();
}

void GBAudioModule_RamWaveGenerator::Reset()
{
    IGBAudioModule::Reset();
    m_SampleIdx = 0;
    m_Counter = (2048 - GetFrequency()) * 2;
}

void GBAudioModule_RamWaveGenerator::Tick()
{
    if ((m_Registers[AUDIO_CHANNEL_NR0_IDX] & 0x80) == 0)
    {
        m_Sample = 0;
    }
    else if ((GetFrequency() == 0) || (--m_Counter == 0))
    {
        m_Counter = (2048 - GetFrequency()) * 2;
        m_Sample = m_SamplesRAM[m_SampleIdx >> 1];
        if ((m_SampleIdx & 0x01) == 0)
        {
            m_Sample >>= 4;
        }
        m_Sample &= 0x0F;
        ++m_SampleIdx &= (AUDIO_SAMPLES_NUM - 1);
    }
}
