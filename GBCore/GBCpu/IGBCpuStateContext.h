#pragma once

#include <QtGlobal>
#include "GBInstruction.h"
#include "IGBCpuState.h"

class IGBCpuStateContext
{
protected:
    IGBCpuStateContext() { }
public:
    virtual ~IGBCpuStateContext() { }
    virtual void SetState(CpuState newStateId, bool isCBInstruction, quint8 opCode) = 0;
    virtual bool GetImeFlag() = 0;
    virtual bool IsCBInstruction() = 0;
    virtual quint16 GetPcAndIncrement() = 0;
    virtual quint8 GetOpCode() = 0;
    virtual bool ExecuteOpCode(GBInstructionContext* ctx, GBBus* bus) = 0;
};
