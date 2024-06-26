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
    virtual void SetState(CpuState newStateId) = 0;
    virtual  void SetCBFlag(bool isCB) = 0;
    virtual bool GetCBFlag() = 0;
    virtual bool GetImeFlag() = 0;
    virtual quint16 GetPcAndIncrement() = 0;
    virtual void SetOpCode(quint8 opCode) = 0;
    virtual quint8 GetOpCode() = 0;
	virtual bool ExecuteOpCode(GBInstructionContext* ctx, IGBBus* bus) = 0;
    virtual void ResetInterruptMode() = 0;
    virtual void SetInterruptMode(quint16 interruptRoutineAddress) = 0;
    virtual bool IsHandlingInterrupt() = 0;
};
