#pragma once

#include <QtGlobal>
#include "GBApu_CommonDefs.h"

class GBApu_ChannelModuleBase
{
protected:
	quint8 (&m_Registers)[AUDIO_CHANNEL_REG_NUM];

    GBApu_ChannelModuleBase(quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]) : m_Registers(registers) { }
public:
    virtual ~GBApu_ChannelModuleBase() { }
    virtual void Tick(bool doAction, quint8* sample) = 0;
    virtual void Reset() = 0;
    virtual void Trigger() = 0;
};
