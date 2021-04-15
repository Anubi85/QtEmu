#pragma once

#include <QtGlobal>
#include "GBApuCommonDefs.h"

class GBApu_ChannelModuleBase
{
protected:
	quint8 (&m_Registers)[AUDIO_CHANNEL_REG_NUM];

	GBApu_ChannelModuleBase(quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]);
public:
	virtual ~GBApu_ChannelModuleBase();
	virtual void Tick(bool doAction, quint8* sample);
	virtual void Reset();
	virtual void Trigger();
};
