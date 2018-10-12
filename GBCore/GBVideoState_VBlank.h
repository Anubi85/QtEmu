#ifndef GBVIDEOSTATE_VBLANK_H
#define GBVIDEOSTATE_VBLANK_H

#include "IGBVideoState.h"

class GBVideoState_VBlank : public IGBVideoState
{
public:
    GBVideoState_VBlank(GBVideo* context);
    void Tick(GBBus* bus) override;
    VideoState GetStateID() override { return VideoState::VBlank; }
};

#endif // GBVIDEOSTATE_VBLANK_H
