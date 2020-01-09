#ifndef GBAPU_SWEEPSQUARECHANNEL_H
#define GBAPU_SWEEPSQUARECHANNEL_H

#include <QtGlobal>
#include "GBApuCommonDefs.h"
#include "GBApu_ChannelBase.h"

class GBApu_LengthCounterModule;
class GBApu_SquareWaveModule;

class GBApu_SweepSquareChannel : public GBApu_ChannelBase
{
private:
	GBApu_SquareWaveModule* m_SquareWave;
	GBApu_LengthCounterModule* m_LengthCounter;

	void Trigger() override;
public:
	GBApu_SweepSquareChannel(quint8& apuStatus);
	~GBApu_SweepSquareChannel() override;
	void ReadRegister(GBBus *bus) override;
	void WriteRegister(GBBus *bus) override;
	void Reset() override;
	void Tick(GBApu_FrameSequencer *sequencer) override;
};

#endif // GBAPU_SWEEPSQUARECHANNEL_H
