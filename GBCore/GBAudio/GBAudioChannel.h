#ifndef GBAUDIOCHANNEL_H
#define GBAUDIOCHANNEL_H

#include <QtGlobal>

class IGBAudioModule;
class GBAudioDac;

class GBAudioChannel
{
private:
    const quint8 c_EnableBitMask;

	IGBAudioModule* m_FrequencySweeper;
    IGBAudioModule* m_WaveGenerator;
    IGBAudioModule* m_LengthCounter;
    IGBAudioModule* m_VolumeManager;
	GBAudioDac* m_Dac;
    quint8* m_ChannelsState;
    quint16 m_TickCounter;

    GBAudioChannel(
            quint8 enableBitMask,
            quint8* channelsState,
			IGBAudioModule* frequencySweeper,
            IGBAudioModule* waveGenerator,
            IGBAudioModule* lengthCounter,
			IGBAudioModule* volumeManager,
			GBAudioDac* dac);
    bool IsSweepTick() { return ((m_TickCounter >> 13) & 0x03) == 0x02; }
    bool IsLengthCounterTick() { return ((m_TickCounter >> 13) & 0x01) == 0x00; }
    bool IsVolumeManagerTick() { return ((m_TickCounter >> 13) & 0x07) == 0x07; }
    bool IsChannelEnabled() { return  (*m_ChannelsState & c_EnableBitMask) != 0; }
    void DisableChannel() { *m_ChannelsState &= !c_EnableBitMask; }
    void EnableChannel() { *m_ChannelsState |= c_EnableBitMask; }
    void PerformModuleTick(bool condition, IGBAudioModule* module);
public:
    ~GBAudioChannel();
    void Reset();
    void Tick();
    void Trigger();
    qreal GetSample();

    static GBAudioChannel* GetSweepSquareChannel(quint8 enableBitMask, quint8* channelsState, quint8* registers);
    static GBAudioChannel* GetSquareChannel(quint8 enableBitMask, quint8* channelsState, quint8* registers);
    static GBAudioChannel* GetWaveChannel(quint8 enableBitMask, quint8* channelsState, quint8* registers, quint8* samplesRam);
    static GBAudioChannel* GetNoiseChannel(quint8 enableBitMask, quint8* channelsState, quint8* registers);
};

#endif // GBAUDIOCHANNEL_H
