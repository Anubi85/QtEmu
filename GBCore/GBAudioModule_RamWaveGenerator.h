#ifndef GBAUDIOMODULE_RAMWAVEGENERATOR_H
#define GBAUDIOMODULE_RAMWAVEGENERATOR_H

#include <QtGlobal>
#include "GBAudioCommonDefs.h"
#include "IGBAudioModule.h"

#define AUDIO_SAMPLES_OFFSET 0x16
#define AUDIO_SAMPLES_NUM 0x20

class GBAudioModule_RamWaveGenerator : public IGBAudioModule
{
private:
    quint8 m_SampleIdx;
    quint16 m_Counter;
    quint8* m_SamplesRAM;

    quint16 GetFrequency() { return static_cast<quint16>((((m_Registers[AUDIO_CHANNEL_NR4_IDX]) << 8) & 0x03) | m_Registers[AUDIO_CHANNEL_NR3_IDX]); }
public:
    GBAudioModule_RamWaveGenerator(quint8* registers);
    void Reset() override;
    void Tick() override;
};

#endif // GBAUDIOMODULE_RAMWAVEGENERATOR_H
