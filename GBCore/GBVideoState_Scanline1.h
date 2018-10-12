#ifndef GBVIDEOSTATE_SCANLINE1_H
#define GBVIDEOSTATE_SCANLINE1_H

#include "IGBVideoState.h"

class GBVideoState_Scanline1 : public IGBVideoState
{
public:
    GBVideoState_Scanline1(GBVideo* context);
    void Tick(GBBus* bus) override;
    VideoState GetStateID() override { return VideoState::Scanline1; }
};

#endif // GBVIDEOSTATE_SCANLINE1_H
