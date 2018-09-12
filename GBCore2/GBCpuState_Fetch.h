#ifndef GBCPUSTATE_FETCH_H
#define GBCPUSTATE_FETCH_H

#include "IGBCpuState.h"

class GBCpuState_Fetch : public IGBCpuState
{
public:
    GBCpuState_Fetch(GBCpu* context);
    void Update(GBBus* bus) override;
};

#endif // GBCPUSTATE_FETCH_H
