#include "GBCpu.h"
#include "GBBus.h"
#include "GBCpuState_Fetch.h"

GBCpu::GBCpu()
{
    Reset();
}

void GBCpu::Reset()
{
    GBComponent::Reset();
    m_Cycles = 0;
    m_PC = 0;
    m_SP = 0;
    m_Registers.All = 0;
    m_State = new GBCpuState_Fetch(this);
}

void GBCpu::Tick(GBBus* bus)
{
    m_Cycles++;
    m_State->Update(bus);
}

void GBCpu::SetState(IGBCpuState* newState)
{
    delete m_State;
    m_State = newState;
}
