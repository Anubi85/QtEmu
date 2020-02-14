#pragma once

#include <QtGlobal>
#include "GBApu_ChannelModuleBase.h"
#include "GBCounter.h"

class GBApu_LengthCounterModule : public GBApu_ChannelModuleBase
{
private:
	const quint8 c_LenghtMask;
	const quint8 c_ChannelMask;
	quint8& m_ApuStatus;
    GBCounter m_Counter;
    quint8 m_OldLength;

    bool IsEnabled() { return (m_Registers[AUDIO_CHANNEL_NRX4_ADDRESS] & 0x40) != 0; }
	quint8 GetLenght() { return  m_Registers[AUDIO_CHANNEL_NRX1_ADDRESS] & c_LenghtMask; }
public:
	GBApu_LengthCounterModule(quint8 lengthMask, quint8 channelMask, quint8& apuStatus, quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]);
    ~GBApu_LengthCounterModule() override { }
    void Reset() override;
	void Tick(bool doAction, quint8* sample) override;
	void Trigger() override;
};
