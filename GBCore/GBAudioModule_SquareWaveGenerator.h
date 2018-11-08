#ifndef GBAUDIOMODULE_SQUAREWAVEGENERATOR_H
#define GBAUDIOMODULE_SQUAREWAVEGENERATOR_H

#include <QtGlobal>
#include "GBAudioCommonDefs.h"
#include "IGBAudioModule.h"

#define DUTY_CYCLES_NUM 4
#define DUTY_CYCLES_SAMPLES_NUM 8

class GBAudioModule_SquareWaveGenerator : public IGBAudioModule
{
private:
    static quint8 s_DutyCycles[DUTY_CYCLES_NUM][DUTY_CYCLES_SAMPLES_NUM];

    quint8 m_SampleIdx;
    quint16 m_Counter;

    quint16 GetFrequency() { return static_cast<quint16>((((m_Registers[AUDIO_CHANNEL_NR4_IDX]) << 8) & 0x03) | m_Registers[AUDIO_CHANNEL_NR3_IDX]); }
    quint8 GetDutyCicle() { return (m_Registers[AUDIO_CHANNEL_NR1_IDX] >> 6) & 0x03; }
public:
    GBAudioModule_SquareWaveGenerator(quint8* registers);
    void Reset() override;
    void Tick() override;
};

#endif // GBAUDIOMODULE_SQUAREWAVEGENERATOR_H
