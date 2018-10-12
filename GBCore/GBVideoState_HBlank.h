#ifndef GBVIDEOSTATE_HBLANK_H
#define GBVIDEOSTATE_HBLANK_H

#include "IGBVideoState.h"

class GBVideoState_HBlank : public IGBVideoState
{
public:
    GBVideoState_HBlank(GBVideo* context);
    void Tick() override;
    VideoState GetStateID() override { return VideoState::HBlank; }
};

#endif // GBVIDEOSTATE_HBLANK_H
