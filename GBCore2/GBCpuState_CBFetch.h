#ifndef GBCPUSTATE_CBFETCH_H
#define GBCPUSTATE_CBFETCH_H

#include "IGBCpuState.h"

class GBCpuState_CBFetch : public IGBCpuState
{
private:
    int m_Count;
public:
    GBCpuState_CBFetch(GBCpu* context);
    void Update(GBBus* bus) override;
    State GetStateID() override { return State::CBFETCH; }
};

#endif // GBCPUSTATE_CBFETCH_H
