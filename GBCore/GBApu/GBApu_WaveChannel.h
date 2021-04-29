#pragma once

#include <QtGlobal>
#include "GBApuCommonDefs.h"
#include "GBApu_ChannelBase.h"

class GBApu_WaveChannel : public GBApu_ChannelBase
{
public:
    GBApu_WaveChannel(quint8& apuStatus, quint8 (&samplesRam)[AUDIO_RAM_SIZE]);
    ~GBApu_WaveChannel() override { }
    void ReadRegister(GBBus *bus) override;
    void WriteRegister(GBBus *bus) override;
};
