#ifndef GBAUDIOMODULE_NOISEWAVEGENERATOR_H
#define GBAUDIOMODULE_NOISEWAVEGENERATOR_H

#include <QtGlobal>
#include "GBAudioCommonDefs.h"
#include "IGBAudioModule.h"

#define LFSR_NEW_BIT_RES_NUM 4

class GBAudioModule_NoiseWaveGenerator : public IGBAudioModule
{
private:
    static bool s_LFSRNewBitCalculator[LFSR_NEW_BIT_RES_NUM];

    quint16 m_LFSR;
    quint16 m_Counter;

    void UpdateLFSR();
    quint16 GetFrequency();
    quint8 GetFrequencyDivider() { return m_Registers[AUDIO_CHANNEL_NR3_IDX] & 0x03; }
    quint8 GetFrequencyShift() { return (m_Registers[AUDIO_CHANNEL_NR3_IDX] & 0xF0) >> 4 ; }
    bool IsLargeWidthMode() { return (m_Registers[AUDIO_CHANNEL_NR3_IDX] & 0x08) == 0; }
public:
    GBAudioModule_NoiseWaveGenerator(quint8* registers);
    void Reset() override;
    void Tick() override;
    void Trigger() override;
};

#endif // GBAUDIOMODULE_NOISEWAVEGENERATOR_H
