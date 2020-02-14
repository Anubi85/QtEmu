#pragma once

#include <QtGlobal>
#include "GBApuCommonDefs.h"
#include "GBApu_Dac.h"

class GBBus;
class GBApu_FrameSequencer;

class GBApu_ChannelBase
{
protected:
	const quint16 c_StartRegAddress;
	quint8& m_ApuStatus;
	quint8 m_Registers[AUDIO_CHANNEL_REG_NUM];
	quint8 m_Sample;
	GBApu_Dac* m_Dac;

	GBApu_ChannelBase(quint16 startRegAddress, quint8& apuStatus);
	virtual void Trigger();
public:
	virtual ~GBApu_ChannelBase();
	virtual void Tick(GBApu_FrameSequencer* sequencer);
	virtual void Reset();
	virtual void ReadRegister(GBBus* bus);
	virtual void WriteRegister(GBBus* bus);
	qreal GetSample() { return m_Dac->GetSample(); }
};
