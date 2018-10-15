#ifndef GBVIDEOSTATE_HBLANK_H
#define GBVIDEOSTATE_HBLANK_H

#include "IGBVideoState.h"

#define VIDEO_MAX_HBLANK 144

class GBVideoState_HBlank : public IGBVideoState
{
public:
	GBVideoState_HBlank(IGBVideoStateContext* context);
    void Tick(GBBus* bus) override;
    VideoState GetStateID() override { return VideoState::HBlank; }
};

#endif // GBVIDEOSTATE_HBLANK_H
