#ifndef GBAUDIO_H
#define GBAUDIO_H

#include "GBComponent.h"
#include "GBUtils.h"
#include "GBAudioChannel_Square.h"

#define AUDIO_MEMORY_SIZE 0x2F
#define AUDIO_ADDRESS_OFFSET 0xFF10

enum class AudioRegister
{
    NR11 = 0xFF11 - AUDIO_ADDRESS_OFFSET,
    NR12 = 0xFF12 - AUDIO_ADDRESS_OFFSET,
    NR13 = 0xFF13 - AUDIO_ADDRESS_OFFSET,
    NR14 = 0xFF14 - AUDIO_ADDRESS_OFFSET,
    NR50 = 0xFF24 - AUDIO_ADDRESS_OFFSET,
    NR51 = 0xFF25 - AUDIO_ADDRESS_OFFSET,
    NR52 = 0xFF26 - AUDIO_ADDRESS_OFFSET,
};

class GBAudio : public GBComponent
{
private:
    GBAudioChannel_Square m_AudioChannel2;
    quint8 m_Registers[AUDIO_MEMORY_SIZE];

    bool IsAddressInRange(quint16 address) { return address >= AUDIO_ADDRESS_OFFSET && address < AUDIO_ADDRESS_OFFSET + AUDIO_MEMORY_SIZE; }
    bool IsAudioEnabled() { return (m_Registers[*AudioRegister::NR52] & 0x80) != 0; }
public:
    GBAudio();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBAUDIO_H
