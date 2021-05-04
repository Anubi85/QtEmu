#pragma once

#include "IGBCpuState.h"

class GBCpuState_InterruptCheck : public IGBCpuState
{
public:
    GBCpuState_InterruptCheck(IGBCpuStateContext* context);
    void Update(GBBus* bus, GBInterruptBus* interruptBus) override;
    CpuState GetStateID() override { return CpuState::InterruptCheck; }
};
