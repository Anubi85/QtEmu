#pragma once

#include <QtGlobal>
#include <qmap.h>
#include "GBApuCommonDefs.h"

class GBBus;
class GBApu_ChannelBase;

class GBApu_Mixer
{
private:
	quint8 m_NR50;
	quint8 m_NR51;
	GBApu_ChannelBase* (&m_Channels)[AUDIO_CHANNELS_NUM];
	qreal m_SampleR;
	qreal m_SampleL;

	bool IsChannelEnabled(quint8 enableMask) { return (m_NR51 & enableMask) != 0; }
	quint8 GetVolume(bool isRight);
	qreal ComputeSample(bool isRight);
public:
	GBApu_Mixer(GBApu_ChannelBase* (&channels)[AUDIO_CHANNELS_NUM]);
	~GBApu_Mixer() {}
	void Reset();
	void Tick(quint8 masterVolume);
	void ReadRegister(GBBus* bus);
	void WriteRegister(GBBus* bus);
	qreal GetSampleR() { return m_SampleR; }
	qreal GetSampleL() { return m_SampleL; }
};
