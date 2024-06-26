#pragma once

#include "IGBCpuState.h"

class GBCpuState_Decode : public IGBCpuState
{
public:
    GBCpuState_Decode(IGBCpuStateContext* context) : IGBCpuState(context) { }
	void Update(GBBus* bus) override;
    CpuState GetStateID() override { return CpuState::Decode; }
};
