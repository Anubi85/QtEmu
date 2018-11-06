#ifndef GBAUDIOCHANNEL_H
#define GBAUDIOCHANNEL_H

#include <QtGlobal>

class GBFrequencySweeper;
class IGBWaveGenerator;
class GBLengthCounter;
class IGBVolumeManager;

class GBAudioChannel
{
private:
    GBFrequencySweeper* m_FrequencySweeper;
    IGBWaveGenerator* m_WaveGenerator;
    GBLengthCounter* m_LengthCounter;
    IGBVolumeManager* m_VolumeManager;
    quint16 m_TickCounter;

    GBAudioChannel(
            GBFrequencySweeper* frequencySweeper,
            IGBWaveGenerator* waveGenerator,
            GBLengthCounter* lengthCounter,
            IGBVolumeManager* volumeManager);
    bool IsSweepTick() { return ((m_TickCounter >> 13) & 0x03) == 0x02; }
    bool IsLengthCounterTick() { return ((m_TickCounter >> 13) & 0x01) == 0x00; }
    bool IsVolumeManagerTick() { return ((m_TickCounter >> 13) & 0x07) == 0x07; }
public:
    ~GBAudioChannel();
    void Reset();
    void Tick();

    static GBAudioChannel* GetSweepSquareChannel(quint8* registers);
    static GBAudioChannel* GetSquareChannel(quint8* registers);
};

#endif // GBAUDIOCHANNEL_H
