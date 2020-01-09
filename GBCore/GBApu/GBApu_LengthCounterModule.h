#ifndef GBAPU_LENGHCOUNTERMODULE_H
#define GBAPU_LENGHCOUNTERMODULE_H

#include <QtGlobal>
#include "GBApu_ChannelModuleBase.h"

class GBApu_LengthCounterModule : public GBApu_ChannelModuleBase
{
private:
	const quint8 c_LenghtMask;
	const quint8 c_ChannelMask;
	quint8& m_ApuStatus;

	quint8 GetLenght() { return  m_Registers[AUDIO_CHANNEL_NRX1_ADDRESS] & c_LenghtMask; }
	void SetLenght(quint8 value);
public:
	GBApu_LengthCounterModule(quint8 lengthMask, quint8 channelMask, quint8& apuStatus, quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]);
	~GBApu_LengthCounterModule() override {}
	void Reset() override {}
	void Tick(bool doAction, quint8* sample) override;
	void Trigger() override;
};

#endif // GBAPU_LENGHCOUNTERMODULE_H
