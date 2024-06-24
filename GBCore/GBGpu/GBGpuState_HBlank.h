#pragma once

#include "IGBGpuState.h"

#define VIDEO_MAX_HBLANK 144

class GBGpuState_HBlank : public IGBGpuState
{
public:
    GBGpuState_HBlank(IGBGpuStateContext* context) : IGBGpuState(context) { }
	void Tick(IGBBus* bus) override;
    GpuState GetStateID() override { return GpuState::HBlank; }
};
