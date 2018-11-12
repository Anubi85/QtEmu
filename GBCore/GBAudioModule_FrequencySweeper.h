#ifndef GBAUDIOMODULE_FREQUENCYSWEEPER_H
#define GBAUDIOMODULE_FREQUENCYSWEEPER_H

#include <QtGlobal>
#include "GBAudioCommonDefs.h"
#include "IGBAudioModule.h"

#define FREQUENCY_MAX_VALUE 0x07FF

class GBAudioModule_FrequencySweeper : public IGBAudioModule
{
private:
    quint8 m_PeriodCounter;
    quint16 m_ShadowFrequency;

    quint16 GetFrequency() { return static_cast<quint16>(((m_Registers[AUDIO_CHANNEL_NR4_IDX] & 0x03) << 8) | m_Registers[AUDIO_CHANNEL_NR3_IDX]); }
    quint8 GetShift() { return m_Registers[AUDIO_CHANNEL_NR0_IDX] & 0x07; }
    bool ShallIncrease(quint8 NRx0) { return (NRx0 & 0x08) == 0; }
    bool ShallNegate() { return (m_Registers[AUDIO_CHANNEL_NR0_IDX] & 0x08) == 0; }
    quint8 GetPeriod() { return (m_Registers[AUDIO_CHANNEL_NR0_IDX] & 0x70) >> 4; }
    void ComputeNewFrequency();
public:
    GBAudioModule_FrequencySweeper(quint8* registers);
    void Reset() override;
    void Tick() override;
    void Trigger() override;
};

#endif // GBAUDIOMODULE_FREQUENCYSWEEPER_H
