#ifndef GBAUDIOCHANNEL_SWEEPSQUARE_H
#define GBAUDIOCHANNEL_SWEEPSQUARE_H

#include "GBAudioChannel_Square.h"

#define SWEEP_SQUARE_CHANNEL_ADDRESS_OFFSET 0xFF10

class GBAudioChannel_SweepSquare : public GBAudioChannel_Square
{
public:
    GBAudioChannel_SweepSquare();
};

#endif // GBAUDIOCHANNEL_SWEEPSQUARE_H
