#pragma once

#include "GBBus.h"
#include "IGBCpuState.h"

class GBCpuState_Error : public IGBCpuState
{
public:
    GBCpuState_Error(IGBCpuStateContext* context) : IGBCpuState(context) { }
    void Update(GBBus* bus, GBInterruptBus* interruptBus) override { Q_UNUSED(bus) Q_UNUSED(interruptBus) }
    CpuState GetStateID() override { return CpuState::Error; }
};
