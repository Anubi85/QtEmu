#ifndef GBAUDIO_H
#define GBAUDIO_H

#include "GBComponent.h"
#include "GBUtils.h"
#include "GBAudioCommonDefs.h"
#include "GBAudioChannel.h"

#define AUDIO_MEMORY_SIZE 0x2F
#define AUDIO_ADDRESS_OFFSET 0xFF10

enum class AudioRegister
{
    NR10 = 0xFF10 - AUDIO_ADDRESS_OFFSET,
    NR11 = 0xFF11 - AUDIO_ADDRESS_OFFSET,
    NR12 = 0xFF12 - AUDIO_ADDRESS_OFFSET,
    NR13 = 0xFF13 - AUDIO_ADDRESS_OFFSET,
    NR14 = 0xFF14 - AUDIO_ADDRESS_OFFSET,
    NR21 = 0xFF16 - AUDIO_ADDRESS_OFFSET,
    NR22 = 0xFF17 - AUDIO_ADDRESS_OFFSET,
    NR23 = 0xFF18 - AUDIO_ADDRESS_OFFSET,
    NR24 = 0xFF19 - AUDIO_ADDRESS_OFFSET,
    NR30 = 0xFF1A - AUDIO_ADDRESS_OFFSET,
    NR31 = 0xFF1B - AUDIO_ADDRESS_OFFSET,
    NR32 = 0xFF1C - AUDIO_ADDRESS_OFFSET,
    NR33 = 0xFF1D - AUDIO_ADDRESS_OFFSET,
    NR34 = 0xFF1E - AUDIO_ADDRESS_OFFSET,
    NR41 = 0xFF20 - AUDIO_ADDRESS_OFFSET,
    NR42 = 0xFF21 - AUDIO_ADDRESS_OFFSET,
    NR43 = 0xFF22 - AUDIO_ADDRESS_OFFSET,
    NR44 = 0xFF23 - AUDIO_ADDRESS_OFFSET,
    NR50 = 0xFF24 - AUDIO_ADDRESS_OFFSET,
    NR51 = 0xFF25 - AUDIO_ADDRESS_OFFSET,
    NR52 = 0xFF26 - AUDIO_ADDRESS_OFFSET,
};

class GBAudio : public GBComponent
{
private:
    GBAudioChannel* m_AudioChannel1;
    GBAudioChannel* m_AudioChannel2;
    GBAudioChannel* m_AudioChannel3;
    GBAudioChannel* m_AudioChannel4;
    quint8 m_Registers[AUDIO_MEMORY_SIZE];

    quint8 ReadAudioRegister(quint8 regAddress);
    void WriteAudioRegister(quint8 regAddress, quint8 value);
    bool IsAddressInRange(quint16 address) { return address >= AUDIO_ADDRESS_OFFSET && address < AUDIO_ADDRESS_OFFSET + AUDIO_MEMORY_SIZE; }
    bool IsAudioEnabled() { return (m_Registers[*AudioRegister::NR52] & 0x80) != 0; }
public:
    GBAudio();
    ~GBAudio();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBAUDIO_H
