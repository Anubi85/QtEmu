#ifndef GBCPUSTATE_DECODE_H
#define GBCPUSTATE_DECODE_H

#include "IGBCpuState.h"

class GBCpuState_Decode : public IGBCpuState
{
private:
    bool m_IsCB;
public:
    GBCpuState_Decode(GBCpu* context, bool isCB);
    void Update(GBBus* bus) override;
    State GetStateID() override { return State::DECODE; }
};

#endif // GBCPUSTATE_DECODE_H
