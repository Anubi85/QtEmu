#ifndef IGBCPUSTATE_H
#define IGBCPUSTATE_H

class GBBus;
class GBCpu;

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
    GBCpu* m_Context;
    IGBCpuState(GBCpu* context);
public:
    virtual ~IGBCpuState();
    virtual void Update(GBBus* bus) = 0;
    virtual CpuState GetStateID() = 0;
};

#endif // IGBCPUSTATE_H
