#pragma once

#include <QtGlobal>
#include "GBMemoryMap.h"
#include "GBApu_CommonDefs.h"
#include "GBApu_ChannelBase.h"

class GBApu_WaveChannel : public GBApu_ChannelBase
{
public:
	GBApu_WaveChannel(quint8& apuStatus, quint8 (&samplesRam)[APU_RAM_SIZE]);
    ~GBApu_WaveChannel() override { }
	void ReadRegister(IGBBus *bus) override;
	void WriteRegister(IGBBus *bus) override;
};
