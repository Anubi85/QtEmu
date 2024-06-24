#pragma once

#include "IGBGpuState.h"

class GBGpuState_VBlank : public IGBGpuState
{
public:
    GBGpuState_VBlank(IGBGpuStateContext* context) : IGBGpuState(context) { }
	void Tick(IGBBus* bus) override;
    GpuState GetStateID() override { return GpuState::VBlank; }
};
