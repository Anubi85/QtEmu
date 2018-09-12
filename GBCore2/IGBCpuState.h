#ifndef IGBCPUSTATE_H
#define IGBCPUSTATE_H

class GBBus;
class GBCpu;

class IGBCpuState
{
protected:
    GBCpu* m_Context;
public:
    IGBCpuState(GBCpu* context);
    virtual ~IGBCpuState();
    virtual void Update(GBBus* bus);
};

#endif // IGBCPUSTATE_H
