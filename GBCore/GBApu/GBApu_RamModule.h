#pragma once

#include <QtGlobal>
#include "GBApu_ChannelModuleBase.h"
#include "GBCounter.h"

class GBApu_RamModule : public GBApu_ChannelModuleBase
{
private:
    quint8 m_SampleIdx;
    GBCounter m_FrequencyCounter;

    quint8 GetVolume() { return (m_Registers[AUDIO_CHANNEL_NRX2_ADDRESS] & 0x60) >> 5; }
    quint16 GetFrequencyCount();
public:
    GBApu_RamModule(quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]) : GBApu_ChannelModuleBase(registers) { }
    ~GBApu_RamModule() override { }
    void Reset() override;
    void Tick(bool doAction, quint8 *sample) override;
    void Trigger() override;
};
