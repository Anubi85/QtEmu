#ifndef GBAUDIOCHANNEL_H
#define GBAUDIOCHANNEL_H

class IGBAudioChannelContext;
class GBFrequencySweeper;
class IGBWaveGenerator;

class GBAudioChannel
{
private:
    IGBAudioChannelContext* m_Context;
    GBFrequencySweeper* m_FrequencySweeper;
    IGBWaveGenerator* m_WaveGenerator;
public:
    GBAudioChannel(IGBAudioChannelContext* context, GBFrequencySweeper* frequencySweeper, IGBWaveGenerator* waveGenerator);
    ~GBAudioChannel();
    void Reset();
    void Tick();
};

#endif // GBAUDIOCHANNEL_H
