#include "GBApu_FrequencySweeperModule.h"

GBApu_FrequencySweeperModule::GBApu_FrequencySweeperModule(quint8& apuStatus, quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]) :
    GBApu_ChannelModuleBase(registers),
    m_ApuStatus(apuStatus)
{
}

quint16 GBApu_FrequencySweeperModule::ComputeNewFrequency()
{
    quint16 deltaFrequency = m_ShadowFrequency >> GetShiftValue();
    if (IsAddMode())
    {
        return m_ShadowFrequency + deltaFrequency;
    }
    else
    {
        return m_ShadowFrequency - deltaFrequency;
    }
}
