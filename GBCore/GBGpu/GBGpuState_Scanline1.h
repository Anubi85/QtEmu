#pragma once

#include "IGBGpuState.h"

class GBGpuState_Scanline1 : public IGBGpuState
{
public:
    GBGpuState_Scanline1(IGBGpuStateContext* context) : IGBGpuState(context) { }
    void Tick(GBBus* bus) override;
    GpuState GetStateID() override { return GpuState::Scanline1; }
};
