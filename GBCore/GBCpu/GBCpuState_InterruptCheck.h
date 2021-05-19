#pragma once

#include "IGBCpuState.h"
#include "GBInterruptBus.h"

class GBCpuState_InterruptCheck : public IGBCpuState
{
private:
    static quint16 s_InterruptRoutineAddress[INTERRUPT_NUM];
public:
    GBCpuState_InterruptCheck(IGBCpuStateContext* context) : IGBCpuState(context) { }
    void Update(GBBus* bus, GBInterruptBus* interruptBus) override;
    CpuState GetStateID() override { return CpuState::InterruptCheck; }
};
