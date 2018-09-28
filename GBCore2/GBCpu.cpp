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

void GBCpu::SetFlag(Flag flagMask, bool value)
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
        if (context->GetY() != *CpuRegister::F)
        {
            m_Registers.Single[context->GetY()] = bus->GetData();
            return true;
        }
        else
        {
            bus->SetAddress(m_Registers.Double[*CpuRegister::HL]);
            //no need to change the data, it has just be read and no one change it!
            //Gameboy harware cannot read and write from bus in the same cycle!
            //Write request will be set in the next cycle
            context->AdvanceStep();
            return false;
        }
    case 2:
        bus->RequestWrite();
        return true;

    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::LD_r1_r2(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        if (context->GetY() != *CpuRegister::F && context->GetZ() != *CpuRegister::F)
        {
            m_Registers.Single[context->GetY()] = m_Registers.Single[context->GetZ()];
            return true;
        }
        else
        {
            bus->SetAddress(m_Registers.Double[*CpuRegister::HL]);
            if (context->GetZ() == *CpuRegister::F)
            {
                bus->RequestRead();
            }
            context->AdvanceStep();
            return false;
        }
    case 1:
        if (context->GetY() == *CpuRegister::F)
        {
            bus->SetData(m_Registers.Single[context->GetZ()]);
            bus->RequestWrite();
        }
        else
        {
            m_Registers.Single[context->GetY()] = bus->GetData();
        }
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::LD_addr_A(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        if (context->GetW() != *CpuRegister::AF)
        {
            bus->SetAddress(m_Registers.Double[context->GetW()]);
            bus->SetData(m_Registers.Single[*CpuRegister::A]);
        }
        else
        {
            bus->SetAddress(m_PC++);
            bus->RequestRead();
        }
        context->AdvanceStep();
        return false;
    case 1:
        if (context->GetW() != *CpuRegister::AF)
        {
            bus->RequestWrite();
            return true;
        }
        else
        {
            context->SetLSB(bus->GetData());
            bus->SetAddress(m_PC++);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
    case 2:
        context->SetMSB(bus->GetData());
        bus->SetAddress(context->Get16BitData());
        bus->SetData(m_Registers.Single[*CpuRegister::A]);
        context->AdvanceStep();
        return false;
    case 3:
        bus->RequestWrite();
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::LD_A_addr(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        if (context->GetW() != *CpuRegister::AF)
        {
            bus->SetAddress(m_Registers.Double[context->GetW()]);
            bus->RequestRead();
        }
        else
        {
            bus->SetAddress(m_PC++);
            bus->RequestRead();
        }
        context->AdvanceStep();
        return false;
    case 1:
        if (context->GetW() != *CpuRegister::AF)
        {
            m_Registers.Single[*CpuRegister::A] = bus->GetData();
            return true;
        }
        else
        {
            context->SetLSB(bus->GetData());
            bus->SetAddress(m_PC++);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
    case 2:
        context->SetMSB(bus->GetData());
        bus->SetAddress(context->Get16BitData());
        bus->RequestRead();
        context->AdvanceStep();
        return false;
    case 3:
        m_Registers.Single[*CpuRegister::A] = bus->GetData();
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::LD_off_A(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        //Check offset source
        if (context->GetBit(Bit::Bit1))
        {
            //Compute the address
            bus->SetAddress(0xFF00 | m_Registers.Single[*CpuRegister::C]);
        }
        else
        {
            bus->SetAddress(m_PC++);
            bus->RequestRead();
        }
        context->AdvanceStep();
        return false;
    case 1:
        //Check offset source
        if (context->GetBit(Bit::Bit1))
        {
            bus->SetData(m_Registers.Single[*CpuRegister::A]);
            bus->RequestWrite();
            return true;
        }
        else
        {
            //Compute the address
            bus->SetAddress(0xFF00 | bus->GetData());
            context->AdvanceStep();
            return false;
        }
    case 2:
        bus->SetData(m_Registers.Single[*CpuRegister::A]);
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
        if (context->GetZ() == *CpuRegister::F)
        {
            bus->SetAddress(context->GetX() == 0b11 ? m_PC++ : m_Registers.Double[*CpuRegister::HL]);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
        else
        {
            m_Registers.Single[*CpuRegister::A] ^= m_Registers.Single[context->GetZ()];
            SetFlag(Flag::Z, m_Registers.Single[*CpuRegister::A] == 0);
            SetFlag(Flag::N, false);
            SetFlag(Flag::H, false);
            SetFlag(Flag::C, false);
            return true;
        }
    case 1:
        m_Registers.Single[*CpuRegister::A] ^= bus->GetData();
        SetFlag(Flag::Z, m_Registers.Single[*CpuRegister::A] == 0);
        SetFlag(Flag::N, false);
        SetFlag(Flag::H, false);
        SetFlag(Flag::C, false);
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::CP(GBInstructionContext* context,  GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        if (context->GetZ() == *CpuRegister::F)
        {
            bus->SetAddress(context->GetX() == 0b11 ? m_PC++ : m_Registers.Double[*CpuRegister::HL]);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
        else
        {
            SetFlag(Flag::Z, m_Registers.Single[*CpuRegister::A] == m_Registers.Single[context->GetY()]);
            SetFlag(Flag::N, true);
            SetFlag(Flag::H, (m_Registers.Single[*CpuRegister::A] & 0x0F) < (m_Registers.Single[context->GetY()] & 0x0F));
            SetFlag(Flag::C, m_Registers.Single[*CpuRegister::A] < m_Registers.Single[context->GetY()]);
            return true;
        }
    case 1:
        SetFlag(Flag::Z, m_Registers.Single[*CpuRegister::A] == bus->GetData());
        SetFlag(Flag::N, true);
        SetFlag(Flag::H, (m_Registers.Single[*CpuRegister::A] & 0x0F) < (bus->GetData() & 0x0F));
        SetFlag(Flag::C, m_Registers.Single[*CpuRegister::A] < bus->GetData());
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::INC_r(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        if (context->GetY() != *CpuRegister::F)
        {
            m_Registers.Single[context->GetY()]++;
            SetFlag(Flag::Z, m_Registers.Single[context->GetY()] == 0);
            SetFlag(Flag::N, false);
            SetFlag(Flag::H, (m_Registers.Single[context->GetY()] & 0x0F) == 0);
            return true;
        }
        else
        {
            bus->SetAddress(m_Registers.Double[*CpuRegister::HL]);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
    case 1:
        //no need to set address, it is the same of previous step
        bus->SetData(bus->GetData() + 1);
        SetFlag(Flag::Z, bus->GetData() == 0);
        SetFlag(Flag::N, false);
        SetFlag(Flag::H, (bus->GetData() & 0x0F) == 0);
        context->AdvanceStep();
        return false;
    case 2:
        bus->RequestWrite();
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::INC_rr(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        if (context->GetW() == *CpuRegister::AF)
        {
            quint8 tmp = m_SP & 0x00FF;
            tmp++;
            context->SetCarry(tmp == 0);
            m_SP = (m_SP & 0xFF00) | tmp;
        }
        else
        {
            m_Registers.Single[context->GetY() + 1]++;
        }
        context->AdvanceStep();
        return false;
    case 1:
        if(context->GetCarry())
        {
            if (context->GetW() == *CpuRegister::AF)
            {
                m_SP += 0x0100;
            }
            else
            {
                m_Registers.Single[context->GetY()]++;
            }
        }
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
        if (context->GetBit(Bit::Bit3))
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
        if (context->GetBit(Bit::Bit3))
        {
            m_Registers.Single[*CpuRegister::A] = bus->GetData();
        }
        m_Registers.Double[*CpuRegister::HL] -= 1;
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::CALL(GBInstructionContext* context, GBBus* bus)
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
        //Check if condition is specified
        if (!context->GetBit(Bit::Bit5))
        {
            bool jump;
            switch (static_cast<Condition>(context->GetQ()))
            {
            case Condition::Z:
                jump = GetFlag(Flag::Z);
                break;
            case Condition::NZ:
                jump = !GetFlag(Flag::Z);
                break;
            case Condition::C:
                jump = GetFlag(Flag::C);
                break;
            case Condition::NC:
                jump = !GetFlag(Flag::C);
                break;
            }
            if (jump)
            {
                context->AdvanceStep();
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            //No condition required, advance
            context->AdvanceStep();
            return false;
        }
    case 3:
        bus->SetAddress(++m_SP);
        bus->SetData(static_cast<quint8>((m_PC & 0xFF00) >> 8));
        bus->RequestWrite();
        context->AdvanceStep();
        return false;
    case 4:
        bus->SetAddress(++m_SP);
        bus->SetData(static_cast<quint8>(m_PC & 0x00FF));
        bus->RequestWrite();
        context->AdvanceStep();
        return false;
    case 5:
        m_PC = context->Get16BitData();
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
        if (context->GetZ() == *CpuRegister::F)
        {
            bus->SetAddress(m_Registers.Double[*CpuRegister::HL]);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
        else
        {
            SetFlag(Flag::Z, (m_Registers.Single[context->GetZ()] & (1<<context->GetY())) == 0);
            SetFlag(Flag::N, false);
            SetFlag(Flag::H, true);
            return true;
        }
    case 1:
        SetFlag(Flag::Z, (bus->GetData() & (1<<context->GetY())) == 0);
        SetFlag(Flag::N, false);
        SetFlag(Flag::H, true);
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
        if (context->GetBit(Bit::Bit5))
        {
            switch (static_cast<Condition>(context->GetQ()))
            {
            case Condition::NZ:
                jump = !GetFlag(Flag::Z);
                break;
            case Condition::Z:
                jump = GetFlag(Flag::Z);
                break;
            case Condition::NC:
                jump = !GetFlag(Flag::C);
                break;
            case Condition::C:
                jump = GetFlag(Flag::C);
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
