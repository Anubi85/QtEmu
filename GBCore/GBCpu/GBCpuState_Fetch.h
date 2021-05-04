#pragma once

#include <QtGlobal>
#include "IGBCpuState.h"

#define INTERRUPT_NUM 5

class GBCpuState_Fetch : public IGBCpuState
{
private:
    static quint16 s_InterruptRoutineAddress[INTERRUPT_NUM];

    int m_Count;
public:
    GBCpuState_Fetch(IGBCpuStateContext* context) : IGBCpuState(context) { }
    void Reset() override;
    void Update(GBBus* bus, GBInterruptBus* interruptBus) override;
    CpuState GetStateID() override { return CpuState::Fetch; }
};
