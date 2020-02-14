#pragma once

#include <QtGlobal>
#include "GBApu_ChannelModuleBase.h"
#include "GBCounter.h"

#define MAX_FREQUENCY 2047

class GBApu_FrequencySweepModule : public GBApu_ChannelModuleBase
{
private:
    const quint8 c_ChannelMask;
    quint8& m_ApuStatus;
    quint16 m_ShadowFrequency;
    GBCounter m_Counter;

    quint16 GetFrequency() { return static_cast<quint16>(((m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] & 0x07) << 8) | m_Registers[AUDIO_CHANNEL_NRX3_ADDRESS]); }
    quint8 GetShiftValue() { return m_Registers[AUDIO_CHANNEL_NRX0_ADDRESS] & 0x07; }
    quint8 GetSweepCount() { return (m_Registers[AUDIO_CHANNEL_NRX0_ADDRESS] & 0x70) >> 4; }
    bool IsAddMode() { return (m_Registers[AUDIO_CHANNEL_NRX0_ADDRESS] & 0x08) == 0; }
    quint16 ComputeNewFrequency();
    bool OverflowCheck(quint16 newFrequency);
public:
    GBApu_FrequencySweepModule(quint8 channelMask, quint8& apuStatus, quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]);
    ~GBApu_FrequencySweepModule() override { }
    void Reset() override;
    void Tick(bool doAction, quint8 *sample) override;
    void Trigger() override;
};
