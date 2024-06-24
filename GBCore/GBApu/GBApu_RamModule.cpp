#include "GBApu_RamModule.h"

void GBApu_RamModule::Reset()
{
    m_SampleIdx = 0;
    m_FrequencyCounter.Reload(GetFrequencyCount());
}

quint16 GBApu_RamModule::GetFrequencyCount()
{
    quint16 frequency = m_Registers[AUDIO_CHANNEL_NRX3_ADDRESS];
    frequency |= (m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] & 0x7) << 8;
    return (2048 - frequency) * 2;
}

void GBApu_RamModule::Trigger()
{
    m_SampleIdx = 0;
    m_FrequencyCounter.Reload(GetFrequencyCount());
}

quint8 GBApu_RamModule::GetVolumeShift()
{
    quint8 volume = (m_Registers[AUDIO_CHANNEL_NRX2_ADDRESS] & 0x60) >> 5;
    return volume > 0 ? (volume - 1) : 4;
}

quint8 GBApu_RamModule::GetSample()
{
    quint8 sample = m_SamplesRam[m_SampleIdx / 2];
    if ((m_SampleIdx & 0x01) == 0)
    {
        //use upper nibble
        sample >>= 4;
    }
    return sample & 0x0F;
}

void GBApu_RamModule::Tick(bool doAction, quint8 *sample)
{
    Q_UNUSED(doAction)
    m_FrequencyCounter.Tick();
    if (m_FrequencyCounter.IsZero())
    {
        m_FrequencyCounter.Reload(GetFrequencyCount());
		m_SampleIdx = (m_SampleIdx + 1) % APU_RAM_SIZE;
    }
    *sample = GetSample() >> GetVolumeShift();
}
