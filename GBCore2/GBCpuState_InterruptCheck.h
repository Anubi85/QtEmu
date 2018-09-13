#ifndef GBCPUSTATE_INTERRUPTCHECK_H
#define GBCPUSTATE_INTERRUPTCHECK_H

#include "IGBCpuState.h"

class GBCpuState_InterruptCheck : public IGBCpuState
{
public:
    GBCpuState_InterruptCheck(GBCpu* context);
    void Update(GBBus* bus) override;
    State GetStateID() override { return State::INTERRUPT_CHECK; }
};

#endif // GBCPUSTATE_INTERRUPTCHECK_H
