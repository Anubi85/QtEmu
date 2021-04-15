#pragma once

#include <QtGlobal>
#include "GBCounter.h"

#define LENGTH_COUNT 0x04000
#define VOLUME_COUNT 0x10000
#define FREQUENCY_COUNT 0x08000

class GBApu_FrameSequencer
{
private:
    GBCounter m_LengthCounter;
    GBCounter m_VolumeCounter;
    GBCounter m_FrequencyCounter;

public:
    GBApu_FrameSequencer(){ }
    ~GBApu_FrameSequencer() { }
    void Tick();
    bool IsLengthCounterTick() { return m_LengthCounter.IsZero(); }
    bool IsVolumeEnvelopeTick() { return m_VolumeCounter.IsZero(); }
    bool IsFrequencySweepTick() { return m_FrequencyCounter.IsZero(); }
    void Reset();
};
