#pragma once

#include "IGBGpuState.h"

#define VIDEO_MAX_HBLANK 144

class GBGpuState_HBlank : public IGBGpuState
{
public:
    GBGpuState_HBlank(IGBGpuStateContext* context);
    void Tick(GBBus* bus) override;
    VideoState GetStateID() override { return VideoState::HBlank; }
};
