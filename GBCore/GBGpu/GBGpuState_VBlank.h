#pragma once

#include "IGBGpuState.h"

class GBGpuState_VBlank : public IGBGpuState
{
public:
    GBGpuState_VBlank(IGBGpuStateContext* context);
    void Tick(GBBus* bus) override;
    VideoState GetStateID() override { return VideoState::VBlank; }
};
