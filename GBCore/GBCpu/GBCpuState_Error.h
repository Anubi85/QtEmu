#pragma once

#include "GBInternalBus.h"
#include "IGBCpuState.h"

class GBCpuState_Error : public IGBCpuState
{
public:
    GBCpuState_Error(IGBCpuStateContext* context) : IGBCpuState(context) { }
	void Update(GBBus* bus) override { Q_UNUSED(bus) }
    CpuState GetStateID() override { return CpuState::Error; }
};
