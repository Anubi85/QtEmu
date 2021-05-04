#pragma once

class GBBus;
class GBInterruptBus;
class IGBCpuStateContext;

#define CPU_STATES_NUM 5

enum class CpuState
{
    Fetch,
    Decode,
    Execute,
    InterruptCheck,
    Error
};

class IGBCpuState
{
protected:
    IGBCpuStateContext* m_Context;
    IGBCpuState(IGBCpuStateContext* context);
public:
    virtual ~IGBCpuState();
    virtual void Reset() { }
    virtual void Update(GBBus* bus, GBInterruptBus* interruptBus) = 0;
    virtual CpuState GetStateID() = 0;
};
