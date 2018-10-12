#ifndef GBVIDEOSTATE_SUSPENDED_H
#define GBVIDEOSTATE_SUSPENDED_H

#include "IGBVideoState.h"

class GBVideoState_Suspended : public IGBVideoState
{
public:
    GBVideoState_Suspended(GBVideo* context);
    void Tick() override;
    VideoState GetStateID() override { return VideoState::Suspended; }
};

#endif // GBVIDEOSTATE_SUSPENDED_H
