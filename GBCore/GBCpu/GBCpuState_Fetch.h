#pragma once

#include <QtGlobal>
#include "IGBCpuState.h"

class GBCpuState_Fetch : public IGBCpuState
{
private:
    int m_Count;
public:
    GBCpuState_Fetch(IGBCpuStateContext* context) : IGBCpuState(context) { }
    void Reset() override;
    void Update(GBBus* bus, GBInterruptBus* interruptBus) override;
    CpuState GetStateID() override { return CpuState::Fetch; }
};
