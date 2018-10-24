#ifndef GBAUDIOCHANNEL_SWEEPSQUARE_H
#define GBAUDIOCHANNEL_SWEEPSQUARE_H

#include "GBAudioChannelBase.h"

#define SWEEP_SQUARE_CHANNEL_ADDRESS_OFFSET 0xFF10

class GBAudioChannel_SweepSquare : public GBAudioChannelBase
{
private:
    bool IsAddressInRange(quint16 address) override { return address >= SWEEP_SQUARE_CHANNEL_ADDRESS_OFFSET && address < (SWEEP_SQUARE_CHANNEL_ADDRESS_OFFSET + AUDIO_CHANNEL_REG_SIZE); }
    quint8 ReadRegister(AudioChannelRegister reg) override;
    void WriteRegister(AudioChannelRegister reg, quint8 value) override;
public:
    GBAudioChannel_SweepSquare();
    void Tick(GBBus* bus) override;
};

#endif // GBAUDIOCHANNEL_SWEEPSQUARE_H
