#ifndef GBCPUSTATE_FETCH_H
#define GBCPUSTATE_FETCH_H

#include <QtGlobal>
#include "IGBCpuState.h"

#define INTERRUPT_NUM 5

class GBCpuState_Fetch : public IGBCpuState
{
private:
    static quint16 s_InterruptRoutineAddress[INTERRUPT_NUM];

    int m_Count;
public:
    GBCpuState_Fetch(GBCpu* context, bool isCB);
    void Update(GBBus* bus) override;
    CpuState GetStateID() override { return CpuState::Fetch; }
};

#endif // GBCPUSTATE_FETCH_H
