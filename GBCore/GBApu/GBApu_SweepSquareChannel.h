#pragma once

#include <QtGlobal>
#include "GBApu_CommonDefs.h"
#include "GBApu_ChannelBase.h"

class GBApu_SweepSquareChannel : public GBApu_ChannelBase
{
public:
	GBApu_SweepSquareChannel(quint8& apuStatus);
    ~GBApu_SweepSquareChannel() override { }
	void ReadRegister(GBBus *bus) override;
	void WriteRegister(GBBus *bus) override;
};
