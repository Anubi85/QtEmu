#pragma once

#include <QtGlobal>
#include "GBApu_ChannelModuleBase.h"
#include "GBCounter.h"

class GBApu_VolumeEnvelopeModule : public GBApu_ChannelModuleBase
{
private:
    quint8 m_CurrentVolume;
    GBCounter m_Counter;

    quint8 GetStartingVolume() { return (m_Registers[AUDIO_CHANNEL_NRX2_ADDRESS] & 0xF0) >> 4; }
    bool IsAddMode() { return (m_Registers[AUDIO_CHANNEL_NRX2_ADDRESS] & 0x08) != 0; }
    quint8 GetPeriod() { return m_Registers[AUDIO_CHANNEL_NRX2_ADDRESS] & 0x07; }
public:
    GBApu_VolumeEnvelopeModule(quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]) : GBApu_ChannelModuleBase(registers) { }
    ~GBApu_VolumeEnvelopeModule() override { }
    void Reset() override;
    void Tick(bool doAction, quint8 *sample) override;
    void Trigger() override;
};
