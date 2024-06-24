#pragma once

#include "IGBCpuState.h"
#include "GBInstruction.h"
#include "GBInstructionContext.h"

class GBCpuState_Execute : public IGBCpuState
{
private:
    GBInstructionContext m_InstructionContext;
    int m_Count;
public:
    GBCpuState_Execute(IGBCpuStateContext* context) : IGBCpuState(context) { }
    void Reset() override;
	void Update(GBBus* bus) override;
    CpuState GetStateID() override { return CpuState::Execute; }
};
