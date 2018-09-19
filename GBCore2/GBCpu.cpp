#include "GBCpu.h"
#include "GBBus.h"
#include "GBInstructionContext.h"
#include "GBCpuState_Fetch.h"

GBCpu::GBCpu()
{
    Reset();
}

GBCpu::~GBCpu()
{
    delete m_State;
}

void GBCpu::Reset()
{
    GBComponent::Reset();
    m_Cycles = 0;
    m_IME = false;
    m_PC = 0;
    m_SP = 0;
    m_Registers.All = 0;
    m_State = new GBCpuState_Fetch(this, false);
}

void GBCpu::Tick(GBBus* bus)
{
    m_State->Update(bus);
    m_Cycles++;
}

void GBCpu::SetState(IGBCpuState* newState)
{
    delete m_State;
    m_State = newState;
}

void GBCpu::SetFlag(FlagMask flagMask, bool value)
{
    if (value)
    {
        m_Registers.Single[*CpuRegister::F] |= *flagMask;
    }
    else
    {
        m_Registers.Single[*CpuRegister::F] &= ~*flagMask;
    }
}

bool GBCpu::LD_r_n(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        bus->SetAddress(m_PC++);
        bus->RequestRead();
        context->AdvanceStep();
        return false;
    case 1:
        if (context->GetY() != *CpuRegister::ADR_HL)
        {
            m_Registers.Single[context->GetY()] = bus->GetData();
            return true;
        }
        else
        {
            //dummy cycle, Gameboy harware cannot read and write from bus in the same cycle!
            context->AdvanceStep();
            return false;
        }
    case 2:
        bus->SetAddress(m_Registers.Double[*CpuRegister::HL]);
        //no need to change the data, it has just be read and no one change it!
        return true;

    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::LD_oC_A(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        //prepare the bus
        bus->SetAddress(0xFF00 | m_Registers.Single[*CpuRegister::C]);
        bus->SetData(m_Registers.Single[*CpuRegister::A]);
        context->AdvanceStep();
        return false;
    case 1:
        //send the write request, Gameboy hardware cannot do this in the previous cycle, the bus is busy for instruction fetching
        bus->RequestWrite();
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
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
        if (context->GetW() == *CpuRegister::AF)
        {
            m_SP = context->Get16BitData();
        }
        else
        {
            m_Registers.Double[context->GetW()] = context->Get16BitData();
        }
        return true;   
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::XOR(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        if (context->GetZ() == *CpuRegister::ADR_HL)
        {
            bus->SetAddress(context->GetX() == 0b11 ? m_PC++ : m_Registers.Double[*CpuRegister::HL]);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
        else
        {
            m_Registers.Single[*CpuRegister::A] ^= m_Registers.Single[context->GetZ()];
            return true;
        }
    case 1:
        m_Registers.Single[*CpuRegister::A] ^= bus->GetData();
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::LDD(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        bus->SetAddress(m_Registers.Double[*CpuRegister::HL]);
        if (context->GetF())
        {
            bus->RequestRead();
        }
        else
        {
            bus->SetData(m_Registers.Single[*CpuRegister::A]);
            bus->RequestWrite();
        }
        context->AdvanceStep();
        return false;
    case 1:
        if (context->GetF())
        {
            m_Registers.Single[*CpuRegister::A] = bus->GetData();
        }
        m_Registers.Double[*CpuRegister::HL] -= 1;
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::BIT(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        if (context->GetZ() == *CpuRegister::ADR_HL)
        {
            bus->SetAddress(m_Registers.Double[*CpuRegister::HL]);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
        else
        {
            SetFlag(FlagMask::Z, (m_Registers.Single[context->GetZ()] & (1<<context->GetY())) == 0);
            SetFlag(FlagMask::N, false);
            SetFlag(FlagMask::H, true);
            return true;
        }
    case 1:
        SetFlag(FlagMask::Z, (bus->GetData() & (1<<context->GetY())) == 0);
        SetFlag(FlagMask::N, false);
        SetFlag(FlagMask::H, true);
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::JR(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        //read the address offset from memory
        bus->SetAddress(m_PC++);
        bus->RequestRead();
        context->AdvanceStep();
        return false;
    case 1:
        //check if conditional jump
        bool jump = true;
        if (context->GetG())
        {
            switch (static_cast<Condition>(context->GetQ()))
            {
            case Condition::NZ:
                jump = !GetFlag(FlagMask::Z);
                break;
            case Condition::Z:
                jump = GetFlag(FlagMask::Z);
                break;
            case Condition::NC:
                jump = !GetFlag(FlagMask::C);
                break;
            case Condition::C:
                jump = GetFlag(FlagMask::C);
                break;
            }
        }
        if (jump)
        {
            m_PC += static_cast<qint8>(bus->GetData()); //it is a signed value!!
        }
        return true;

    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}
