#ifndef GBAUDIOCHANNEL_H
#define GBAUDIOCHANNEL_H

#include <QtGlobal>

class IGBAudioModule;

class GBAudioChannel
{
private:
    IGBAudioModule* m_FrequencySweeper;
    IGBAudioModule* m_WaveGenerator;
    IGBAudioModule* m_LengthCounter;
    IGBAudioModule* m_VolumeManager;
    quint16 m_TickCounter;

    GBAudioChannel(
            IGBAudioModule* frequencySweeper,
            IGBAudioModule* waveGenerator,
            IGBAudioModule* lengthCounter,
            IGBAudioModule* volumeManager);
    bool IsSweepTick() { return ((m_TickCounter >> 13) & 0x03) == 0x02; }
    bool IsLengthCounterTick() { return ((m_TickCounter >> 13) & 0x01) == 0x00; }
    bool IsVolumeManagerTick() { return ((m_TickCounter >> 13) & 0x07) == 0x07; }
public:
    ~GBAudioChannel();
    void Reset();
    void Tick();

    static GBAudioChannel* GetSweepSquareChannel(quint8* registers);
    static GBAudioChannel* GetSquareChannel(quint8* registers);
    static GBAudioChannel* GetWaveChannel(quint8* registers);
    static GBAudioChannel* GetNoiseChannel(quint8* registers);
};

#endif // GBAUDIOCHANNEL_H
