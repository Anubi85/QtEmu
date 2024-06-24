#pragma once

#include <QtGlobal>
#include <QSemaphore>
#include "GBComponent.h"
#include "GBMemoryMap.h"
#include "GBApu_CommonDefs.h"

#define SAMPLES_BUFFER_SIZE 2024

class IGBBus;
class GBApu_FrameSequencer;
class GBApu_Mixer;
class GBApu_ChannelBase;

class GBApu : public GBComponent
{
private:
	quint8 m_NR52;
	quint8 m_SamplesRam[APU_RAM_SIZE];
	GBApu_ChannelBase* m_Channels[AUDIO_CHANNELS_NUM];
	GBApu_FrameSequencer* m_FrameSequencer;
	GBApu_Mixer* m_Mixer;
    QSemaphore m_SamplesSemaphore;
    bool m_CurrentBuffer;
    quint16 m_SamplesCounter;
    quint8 m_SamplesBuffer[2][SAMPLES_BUFFER_SIZE];

	bool IsAddressInAudioReg(quint16 address) { return address >= APU_REGISTERS_ADDRESS && address < APU_REGISTERS_ADDRESS + APU_REGISTERS_SIZE; }
	bool IsAddressInAudioRam(quint16 address) { return address >= APU_RAM_ADDRESS && address < APU_RAM_ADDRESS + APU_RAM_SIZE; }
	bool IsAudioEnabled(){ return (m_NR52 & 0x80) != 0; }
	void ReadRegister(IGBBus* bus);
	void WriteRegister(IGBBus* bus);
    void AddSamplesToBuffer(quint8 lSample, quint8 rSample);
public:
	GBApu();
	~GBApu() override;
	void Reset() override;
	void Tick(GBBus* bus) override;
    quint32 GetSamplesBufferSize() { return SAMPLES_BUFFER_SIZE; }
    quint8* GetSamples();
};
