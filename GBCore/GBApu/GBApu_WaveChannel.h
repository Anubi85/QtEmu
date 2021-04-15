#pragma once

#include <QtGlobal>
#include "GBApuCommonDefs.h"
#include "GBApu_ChannelBase.h"

class GBApu_WaveChannel : public GBApu_ChannelBase
{
public:
    GBApu_WaveChannel(quint8& apuStatus);
    ~GBApu_WaveChannel() override { }
    void ReadRegister(GBBus *bus) override;
    void WriteRegister(GBBus *bus) override;
};
