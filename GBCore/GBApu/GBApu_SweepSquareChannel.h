#pragma once

#include <QtGlobal>
#include "GBApuCommonDefs.h"
#include "GBApu_ChannelBase.h"

class GBApu_LengthCounterModule;
class GBApu_SquareWaveModule;
class GBApu_FrequencySweepModule;
class GBApu_VolumeEnvelopeModule;

class GBApu_SweepSquareChannel : public GBApu_ChannelBase
{
private:
    GBApu_FrequencySweepModule* m_FrequencySweeper;
	GBApu_SquareWaveModule* m_SquareWave;
	GBApu_LengthCounterModule* m_LengthCounter;
    GBApu_VolumeEnvelopeModule* m_VolumeEnvelope;

	void Trigger() override;
public:
	GBApu_SweepSquareChannel(quint8& apuStatus);
	~GBApu_SweepSquareChannel() override;
	void ReadRegister(GBBus *bus) override;
	void WriteRegister(GBBus *bus) override;
	void Reset() override;
	void Tick(GBApu_FrameSequencer *sequencer) override;
};
