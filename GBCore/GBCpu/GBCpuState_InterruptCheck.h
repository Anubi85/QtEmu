#ifndef GBCPUSTATE_INTERRUPTCHECK_H
#define GBCPUSTATE_INTERRUPTCHECK_H

#include "IGBCpuState.h"

class GBCpuState_InterruptCheck : public IGBCpuState
{
public:
    GBCpuState_InterruptCheck(IGBCpuStateContext* context);
    void Update(GBBus* bus) override;
    CpuState GetStateID() override { return CpuState::InterruptCheck; }
};

#endif // GBCPUSTATE_INTERRUPTCHECK_H
