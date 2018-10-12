#ifndef IGBCPUSTATE_H
#define IGBCPUSTATE_H

class GBBus;
class IGBCpuStateContext;

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
    virtual void Update(GBBus* bus) = 0;
    virtual CpuState GetStateID() = 0;
};

#endif // IGBCPUSTATE_H
