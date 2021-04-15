#include "GBApu_RamModule.h"

void GBApu_RamModule::Reset()
{
    GBApu_ChannelModuleBase::Reset();
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
