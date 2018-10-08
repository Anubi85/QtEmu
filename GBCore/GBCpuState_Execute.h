#ifndef GBCPUSTATE_EXECUTE_H
#define GBCPUSTATE_EXECUTE_H

#include "IGBCpuState.h"
#include "GBInstruction.h"

class GBInstructionContext;

class GBCpuState_Execute : public IGBCpuState
{
private:
    GBInstruction m_Instruction;
    GBInstructionContext* m_InstructionContext;
    int m_Count;
public:
    GBCpuState_Execute(GBCpu* context, GBInstruction inst, GBInstructionContext* instContext);
    void Update(GBBus* bus) override;
    State GetStateID() override { return State::Execute; }
};

#endif // GBCPUSTATE_EXECUTE_H
