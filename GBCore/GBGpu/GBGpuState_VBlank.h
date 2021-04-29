#pragma once

#include "IGBGpuState.h"

class GBGpuState_VBlank : public IGBGpuState
{
public:
    GBGpuState_VBlank(IGBGpuStateContext* context) : IGBGpuState(context) { }
    void Tick(GBBus* bus) override;
    GpuState GetStateID() override { return GpuState::VBlank; }
};
