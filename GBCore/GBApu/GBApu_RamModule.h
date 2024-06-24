#pragma once

#include <QtGlobal>
#include "GBMemoryMap.h"
#include "GBApu_ChannelModuleBase.h"
#include "GBCounter.h"

class GBApu_RamModule : public GBApu_ChannelModuleBase
{
private:
	quint8 (&m_SamplesRam)[APU_RAM_SIZE];
    quint8 m_SampleIdx;
    GBCounter m_FrequencyCounter;

    quint8 GetSample();
    quint8 GetVolumeShift();
    quint16 GetFrequencyCount();
public:
	GBApu_RamModule(quint8 (&registers)[AUDIO_CHANNEL_REG_NUM], quint8 (&samplesRam)[APU_RAM_SIZE]) : GBApu_ChannelModuleBase(registers), m_SamplesRam(samplesRam) { }
    ~GBApu_RamModule() override { }
    void Reset() override;
    void Tick(bool doAction, quint8 *sample) override;
    void Trigger() override;
};
