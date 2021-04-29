#pragma once

#include <QtGlobal>
#include "GBApu_CommonDefs.h"
#include "GBApu_ChannelBase.h"

class GBApu_SquareChannel : public GBApu_ChannelBase
{
public:
    GBApu_SquareChannel(quint8& apuStatus);
    ~GBApu_SquareChannel() override { }
    void ReadRegister(GBBus *bus) override;
    void WriteRegister(GBBus *bus) override;
};
