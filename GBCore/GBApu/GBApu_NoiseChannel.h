#pragma once

#include <QtGlobal>
#include "GBMemoryMap.h"
#include "GBApu_CommonDefs.h"
#include "GBApu_ChannelBase.h"

class GBApu_NoiseChannel : public GBApu_ChannelBase
{
public:
    GBApu_NoiseChannel(quint8& apuStatus);
    ~GBApu_NoiseChannel() override { }
	void ReadRegister(IGBBus *bus) override;
	void WriteRegister(IGBBus *bus) override;
};
