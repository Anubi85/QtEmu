#pragma once

#include "IGBGpuState.h"

class GBGpuState_Suspended : public IGBGpuState
{
public:
    GBGpuState_Suspended(IGBGpuStateContext* context);
    void Tick(GBBus* bus) override;
    VideoState GetStateID() override { return VideoState::Suspended; }
};
