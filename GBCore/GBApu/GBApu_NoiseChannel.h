#pragma once

#include <QtGlobal>
#include "GBApuCommonDefs.h"
#include "GBApu_ChannelBase.h"

class GBApu_NoiseChannel : public GBApu_ChannelBase
{
public:
    GBApu_NoiseChannel(quint8& apuStatus);
    ~GBApu_NoiseChannel() override { }
    void ReadRegister(GBBus *bus) override;
    void WriteRegister(GBBus *bus) override;
};
