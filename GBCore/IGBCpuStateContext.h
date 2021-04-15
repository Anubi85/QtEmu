#ifndef IGBCPUSTATECONTEXT_H
#define IGBCPUSTATECONTEXT_H

#include <QtGlobal>
#include "GBInstruction.h"

class IGBCpuState;

class IGBCpuStateContext
{
protected:
    IGBCpuStateContext();
public:
    virtual ~IGBCpuStateContext();
    virtual void SetState(IGBCpuState* newState) = 0;
    virtual bool GetImeFlag() = 0;
    virtual quint16 GetPcAndIncrement() = 0;
    virtual GBInstruction GetInstruction(quint8 opCpde) = 0;
    virtual GBInstruction GetCBInstruction(quint8 opCode) = 0;
	virtual bool ExecuteOpCode(GBInstruction inst, GBInstructionContext* ctx, GBBus* bus) = 0;
};

#endif // IGBCPUSTATECONTEXT_H
