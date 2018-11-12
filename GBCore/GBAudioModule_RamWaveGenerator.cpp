#include "GBAudioModule_RamWaveGenerator.h"

GBAudioModule_RamWaveGenerator::GBAudioModule_RamWaveGenerator(quint8* registers, quint8* samplesRam) :
    IGBAudioModule(registers)
{
    m_SamplesRAM = samplesRam;
    Reset();
}

void GBAudioModule_RamWaveGenerator::Reset()
{
    IGBAudioModule::Reset();
    m_SampleIdx = 0;
    m_Counter = 0;
    m_Enabled = false;
}

void GBAudioModule_RamWaveGenerator::Trigger()
{

    m_SampleIdx = 0;
    m_Counter = GetCounterValue();
    m_Enabled = (m_Registers[AUDIO_CHANNEL_NR0_IDX] & 0x80) == 0;
}

void GBAudioModule_RamWaveGenerator::Tick()
{
    if (m_Enabled && (--m_Counter == 0))
    {
        m_Counter = GetCounterValue();
        m_Sample = m_SamplesRAM[m_SampleIdx >> 1];
        if ((m_SampleIdx & 0x01) == 0)
        {
            m_Sample >>= 4;
        }
        m_Sample &= 0x0F;
        m_Sample >>= s_VolumeFactors[GetVolume()];
        ++m_SampleIdx &= (AUDIO_SAMPLES_NUM - 1);
    }
}
