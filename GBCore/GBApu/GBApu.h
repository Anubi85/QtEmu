#ifndef GBAPU_H
#define GBAPU_H

#include <QtGlobal>
#include "GBComponent.h"
#include "GBApuCommonDefs.h"

class GBApu_FrameSequencer;
class GBApu_Mixer;
class GBApu_ChannelBase;

class GBApu : public GBComponent
{
private:
	quint8 m_NR52;
	quint8 m_SamplesRam[AUDIO_RAM_SIZE];
	GBApu_ChannelBase* m_Channels[AUDIO_CHANNELS_NUM];
	GBApu_FrameSequencer* m_FrameSequencer;
	GBApu_Mixer* m_Mixer;

	bool IsAddressInAudioReg(quint16 address) { return address >= AUDIO_REG_ADDRESS_OFFSET && address < AUDIO_REG_ADDRESS_OFFSET + AUDIO_REG_SIZE; }
	bool IsAddressInAudioRam(quint16 address) { return address >= AUDIO_RAM_ADDRESS_OFFSET && address < AUDIO_RAM_ADDRESS_OFFSET + AUDIO_RAM_SIZE; }
	bool IsAudioEnabled(){ return (m_NR52 & 0x80) != 0; }
	void ReadRegister(GBBus* bus);
	void WriteRegister(GBBus* bus);
	void ReadSamplesRam(GBBus* bus);
	void WriteSamplesRam(GBBus* bus);
public:
	GBApu();
	~GBApu() override;
	void Reset() override;
	void Tick(GBBus *bus) override;
};

#endif // GBAPU_H
