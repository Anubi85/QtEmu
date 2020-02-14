#pragma once

#include <QtGlobal>
#include "GBApu_ChannelModuleBase.h"
#include "GBCounter.h"

#define DUTY_CYCLES_NUM 4
#define DUTY_CYCLES_SAMPLES 8

class GBApu_SquareWaveModule : public GBApu_ChannelModuleBase
{
private:
	static quint8 s_DutyCycles[DUTY_CYCLES_NUM][DUTY_CYCLES_SAMPLES];

	quint8 m_SampleIdx;
	quint8 m_DutyIdx;
    GBCounter m_FrequencyCounter;

	quint16 GetFrequencyCount();
	quint8 GetDutyCycle() { return (m_Registers[AUDIO_CHANNEL_NRX1_ADDRESS] >> 6) & 0x03; }
public:
    GBApu_SquareWaveModule(quint8 (&registers)[AUDIO_CHANNEL_REG_NUM]) : GBApu_ChannelModuleBase(registers) { }
    ~GBApu_SquareWaveModule() override { }
	void Reset() override;
	void Tick(bool doAction, quint8 *sample) override;
	void Trigger() override;
};
