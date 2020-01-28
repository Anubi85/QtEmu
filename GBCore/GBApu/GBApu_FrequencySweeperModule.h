#ifndef GBAPU_FREQUENCYSWEEPERMODULE_H
#define GBAPU_FREQUENCYSWEEPERMODULE_H

#include <QtGlobal>
#include "GBApu_ChannelModuleBase.h"

class GBApu_FrequencySweeperModule : public GBApu_ChannelModuleBase
{
private:
    quint8& m_ApuStatus;
    quint16 m_ShadowFrequency;

    quint16 GetFrequency() { return static_cast<quint16>(((m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] & 0x07) << 8) | m_Registers[AUDIO_CHANNEL_NRX3_ADDRESS]); }
    quint8 GetShiftValue() { return m_Registers[AUDIO_CHANNEL_NRX0_ADDRESS] & 0x07; }
    quint8 GetSweepCount() { return (m_Registers[AUDIO_CHANNEL_NRX0_ADDRESS] & 0x70) >> 4; }
    bool IsAddMode() { return (m_Registers[AUDIO_CHANNEL_NRX0_ADDRESS] & 0x08) == 0; }
    quint16 ComputeNewFrequency();
public:
    GBApu_FrequencySweeperModule(quint8& apuStatus, quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]);
    ~GBApu_FrequencySweeperModule() override { }
    void Reset() override;
    void Tick(bool doAction, quint8 *sample) override;
    void Trigger() override;
};

#endif // GBAPU_FREQUENCYSWEEPERMODULE_H
