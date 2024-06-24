#pragma once

#include "IGBGpuState.h"

class GBGpuState_Suspended : public IGBGpuState
{
public:
    GBGpuState_Suspended(IGBGpuStateContext* context) : IGBGpuState(context) { }
	void Tick(IGBBus* bus) override;
    GpuState GetStateID() override { return GpuState::Suspended; }
};
