#ifndef GBAUDIO_H
#define GBAUDIO_H

#include "GBComponent.h"

#define NR52_ADDRESS 0xFF26

class GBAudio : public GBComponent
{
private:
    quint8 m_NR52;

    bool IsAddressInRange(quint16 address);
    bool IsAudioEnabled() { return (m_NR52 & 0x80) != 0; }
public:
    GBAudio();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBAUDIO_H
