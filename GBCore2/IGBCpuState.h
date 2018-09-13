#ifndef IGBCPUSTATE_H
#define IGBCPUSTATE_H

class GBBus;
class GBCpu;

enum class State
{
    FETCH,
    CBFETCH,
    DECODE
};

class IGBCpuState
{
protected:
    GBCpu* m_Context;
public:
    IGBCpuState(GBCpu* context);
    virtual ~IGBCpuState();
    virtual void Update(GBBus* bus) = 0;
    virtual State GetStateID() = 0;
};

#endif // IGBCPUSTATE_H
