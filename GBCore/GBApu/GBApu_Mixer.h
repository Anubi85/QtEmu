#pragma once

#include <QtGlobal>
#include <qmap.h>
#include "GBMemoryMap.h"
#include "GBApu_CommonDefs.h"

class IGBBus;
class GBApu_ChannelBase;

class GBApu_Mixer
{
private:
	quint8 m_NR50;
	quint8 m_NR51;
	GBApu_ChannelBase* (&m_Channels)[AUDIO_CHANNELS_NUM];
    quint8 m_SampleR;
    quint8 m_SampleL;

	bool IsChannelEnabled(quint8 enableMask) { return (m_NR51 & enableMask) != 0; }
	quint8 GetVolume(bool isRight);
    quint8 ComputeSample(bool isRight);
public:
    GBApu_Mixer(GBApu_ChannelBase* (&channels)[AUDIO_CHANNELS_NUM]) : m_Channels(channels) { Reset(); }
    ~GBApu_Mixer() { }
	void Reset();
    void Tick();
	void ReadRegister(IGBBus* bus);
	void WriteRegister(IGBBus* bus);
    quint8 GetSampleR() { return m_SampleR; }
    quint8 GetSampleL() { return m_SampleL; }
};
