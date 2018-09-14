#include "GBCpu.h"
#include "GBBus.h"
#include "GBInstructionContext.h"
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
    m_State = new GBCpuState_Fetch(this, false);
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

bool GBCpu::LD_rr_nn(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        bus->SetAddress(m_PC++);
        bus->RequestRead();
        context->AdvanceStep();
        return false;
    case 1:
        context->SetLSB(bus->GetData());
        bus->SetAddress(m_PC++);
        bus->RequestRead();
        context->AdvanceStep();
        return false;
    case 2:
        context->SetMSB(bus->GetData());
        if (context->GetW() == *Register::AF)
        {
            m_SP = context->Get16BitData();
        }
        else
        {
            m_Registers.Double[context->GetW()] = context->Get16BitData();
        }
        return true;
    }
}
