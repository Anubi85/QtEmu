#ifndef GBVIDEOSTATE_SCANLINE2_H
#define GBVIDEOSTATE_SCANLINE2_H

#include "IGBVideoState.h"

class GBVideoState_Scanline2 : public IGBVideoState
{
public:
    GBVideoState_Scanline2(GBVideo* context);
    void Tick() override;
    VideoState GetStateID() override { return VideoState::Scanline2; }
};

#endif // GBVIDEOSTATE_SCANLINE2_H
