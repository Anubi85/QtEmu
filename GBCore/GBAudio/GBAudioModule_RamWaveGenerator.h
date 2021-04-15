#ifndef GBAUDIOMODULE_RAMWAVEGENERATOR_H
#define GBAUDIOMODULE_RAMWAVEGENERATOR_H

#include <QtGlobal>
#include "GBAudioCommonDefs.h"
#include "IGBAudioModule.h"

#define AUDIO_SAMPLES_NUM 0x20
#define VOLUME_FACTORS_NUM 4

class GBAudioModule_RamWaveGenerator : public IGBAudioModule
{
private:
    static quint8 s_VolumeFactors[VOLUME_FACTORS_NUM];

    quint8 m_SampleIdx;
    quint16 m_Counter;
    quint8* m_SamplesRAM;

    quint16 GetFrequency() { return static_cast<quint16>((((m_Registers[AUDIO_CHANNEL_NR4_IDX]) << 8) & 0x03) | m_Registers[AUDIO_CHANNEL_NR3_IDX]); }
    quint16 GetCounterValue() { return (2048 - GetFrequency()) * 2; }
    quint8 GetVolume() { return (m_Registers[AUDIO_CHANNEL_NR2_IDX] &0x60) >> 5; }
public:
    GBAudioModule_RamWaveGenerator(quint8* registers, quint8* samplesRam);
    void Reset() override;
    void Tick() override;
    void Trigger() override;
};

#endif // GBAUDIOMODULE_RAMWAVEGENERATOR_H
