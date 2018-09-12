#ifndef GBCPUSTATE_DECODE_H
#define GBCPUSTATE_DECODE_H

#include "IGBCpuState.h"

class GBCpuState_Decode : public IGBCpuState
{
public:
    GBCpuState_Decode(GBCpu* context);
    void Update(GBBus* bus) override;
};

#endif // GBCPUSTATE_DECODE_H
