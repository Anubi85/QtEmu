#ifndef GBAUDIOCHANNEL_H
#define GBAUDIOCHANNEL_H

class IGBAudioChannelContext;
class IGBWaveGenerator;

class GBAudioChannel
{
private:
    IGBAudioChannelContext* m_Context;
    IGBWaveGenerator* m_WaveGenerator;
public:
    GBAudioChannel(IGBAudioChannelContext* context, IGBWaveGenerator* waveGenerator);
    ~GBAudioChannel();
    void Reset();
    void Tick();
};

#endif // GBAUDIOCHANNEL_H
