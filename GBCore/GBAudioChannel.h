#ifndef GBAUDIOCHANNEL_H
#define GBAUDIOCHANNEL_H

#include <QtGlobal>

class IGBAudioChannelContext;
class GBFrequencySweeper;
class IGBWaveGenerator;
class GBLengthCounter;

class GBAudioChannel
{
private:
    IGBAudioChannelContext* m_Context;
    GBFrequencySweeper* m_FrequencySweeper;
    IGBWaveGenerator* m_WaveGenerator;
    GBLengthCounter* m_LengthCounter;
    quint16 m_TickCounter;

    bool IsSweepTick() { return ((m_TickCounter >> 13) & 0x03) == 0x02; }
    bool IsLengthCounterTick() { return ((m_TickCounter >> 13) & 0x01) == 0x00; }
public:
    GBAudioChannel(IGBAudioChannelContext* context, GBFrequencySweeper* frequencySweeper, IGBWaveGenerator* waveGenerator, GBLengthCounter* lengthCounter);
    ~GBAudioChannel();
    void Reset();
    void Tick();
};

#endif // GBAUDIOCHANNEL_H
