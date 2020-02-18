#pragma once

#include <QtGlobal>
#include "GBApu_ChannelModuleBase.h"
#include "GBCounter.h"

class GBApu_LfsrModule : public GBApu_ChannelModuleBase
{
private:
    GBCounter m_FrequencyCounter;
    quint16 m_LFSR;

    quint8 GetDivisorCode() { return m_Registers[AUDIO_CHANNEL_NRX3_ADDRESS] & 0x07; }
    quint8 GetDivisorShift() { return (m_Registers[AUDIO_CHANNEL_NRX3_ADDRESS] & 0xF0) >> 4; }
    bool Is7BitShift() { return (m_Registers[AUDIO_CHANNEL_NRX3_ADDRESS] & 0x08) != 0; }
public:
    GBApu_LfsrModule(quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]) : GBApu_ChannelModuleBase(registers) { }
    ~GBApu_LfsrModule() override { }
    void Reset() override;
    void Tick(bool doAction, quint8 *sample) override;
    void Trigger() override;
};
