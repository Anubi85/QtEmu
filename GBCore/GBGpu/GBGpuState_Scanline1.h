#pragma once

#include "IGBGpuState.h"

class GBGpuState_Scanline1 : public IGBGpuState
{
public:
    GBGpuState_Scanline1(IGBGpuStateContext* context);
    void Tick(GBBus* bus) override;
    VideoState GetStateID() override { return VideoState::Scanline1; }
};
