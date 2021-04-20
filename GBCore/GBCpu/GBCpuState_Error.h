#pragma once

#include "GBBus.h"
#include "IGBCpuState.h"

class GBCpuState_Error : public IGBCpuState
{
public:
    GBCpuState_Error(IGBCpuStateContext* context) : IGBCpuState(context) { }
    void Update(GBBus* bus) override { bus->Clear(); } //never exit the state and delete any pending request
    CpuState GetStateID() override { return CpuState::Error; }
};
