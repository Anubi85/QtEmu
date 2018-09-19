#ifndef GBAUDIO_H
#define GBAUDIO_H

#include "GBComponent.h"
#include "GBUtils.h"

#define AUDIO_MEMORY_SIZE 0x2F
#define AUDIO_ADDRESS_OFFSET 0xFF10

enum class AudioRegister
{
    NR11 = 0xFF11 - AUDIO_ADDRESS_OFFSET,
    NR52 = 0xFF26 - AUDIO_ADDRESS_OFFSET,
    Invalid,
};

class GBAudio : public GBComponent
{
private:
    QByteArray m_Registers;

    bool IsAddressInRange(quint16 address) { return address >= AUDIO_ADDRESS_OFFSET && address < AUDIO_ADDRESS_OFFSET + AUDIO_MEMORY_SIZE; }
    bool IsAudioEnabled() { return (m_Registers[*AudioRegister::NR52] & 0x80) != 0; }
public:
    GBAudio();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBAUDIO_H
