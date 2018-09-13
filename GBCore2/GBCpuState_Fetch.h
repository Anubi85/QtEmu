#ifndef GBCPUSTATE_FETCH_H
#define GBCPUSTATE_FETCH_H

#include <QtCore>
#include "IGBCpuState.h"

#define INTERRUPT_NUM 5

class GBCpuState_Fetch : public IGBCpuState
{
private:
    static quint16 s_InterruptRoutineAddress[INTERRUPT_NUM];
public:
    GBCpuState_Fetch(GBCpu* context);
    void Update(GBBus* bus) override;
    State GetStateID() override { return State::FETCH; }
};

#endif // GBCPUSTATE_FETCH_H
