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
        if (context->GetX() == 0b11)
        {
            bus->SetAddress(m_PC++);
            bus->RequestRead();
        }
        else
        {
            bus->SetAddress(m_Registers.Double[context->GetW()]);
            bus->SetData(m_Registers.Single[*CpuRegister::A]);
        }
        context->AdvanceStep();
        return false;
    case 1:
        if (context->GetX() == 0b11)
        {
            context->SetLSB(bus->GetData());
            bus->SetAddress(m_PC++);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
        else
        {
            bus->RequestWrite();
            return true;
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
        if (context->GetW() == *CpuRegister::AF)
        {
            bus->SetAddress(m_PC++);
            bus->RequestRead();
        }
        else
        {
            bus->SetAddress(m_Registers.Double[context->GetW()]);
            bus->RequestRead();
        }
        context->AdvanceStep();
        return false;
    case 1:
        if (context->GetW() == *CpuRegister::AF)
        {
            context->SetLSB(bus->GetData());
            bus->SetAddress(m_PC++);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
        else
        {
            m_Registers.Single[*CpuRegister::A] = bus->GetData();
            return true;
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

bool GBCpu::LD_A_off(GBInstructionContext* context, GBBus* bus)
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
        }
        bus->RequestRead();
        context->AdvanceStep();
        return false;
    case 1:
        //Check offset source
        if (context->GetBit(Bit::Bit1))
        {
            m_Registers.Single[*CpuRegister::A] = bus->GetData();
            return true;
        }
        else
        {
            //Compute the address
            bus->SetAddress(0xFF00 | bus->GetData());
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
    case 2:
        m_Registers.Single[*CpuRegister::A] = bus->GetData();
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

bool GBCpu::PUSH(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        //compute the address
        bus->SetAddress(--m_SP);
        context->AdvanceStep();
        return false;
    case 1:
        bus->SetData(m_Registers.Single[context->GetY() + 1]);
        bus->RequestWrite();
        context->AdvanceStep();
        return false;
    case 2:
        //compute the address
        bus->SetAddress(--m_SP);
        context->AdvanceStep();
        return false;
    case 3:
        bus->SetData(m_Registers.Single[context->GetY()]);
        bus->RequestWrite();
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::POP(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        bus->SetAddress(m_SP++);
        bus->RequestRead();
        context->AdvanceStep();
        return false;
    case 1:
        m_Registers.Single[context->GetY()] = bus->GetData();
        bus->SetAddress(m_SP++);
        bus->RequestRead();
        context->AdvanceStep();
        return false;
    case 2:
        m_Registers.Single[context->GetY() + 1] = bus->GetData();
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

bool GBCpu::ADD(GBInstructionContext* context,  GBBus* bus)
{
    quint8 tmp;
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
            tmp = m_Registers.Single[*CpuRegister::A];
            m_Registers.Single[*CpuRegister::A] += m_Registers.Single[context->GetZ()];
            SetFlag(Flag::Z, m_Registers.Single[*CpuRegister::A] == 0);
            SetFlag(Flag::N, false);
            SetFlag(Flag::H, (m_Registers.Single[*CpuRegister::A] & 0x10) != 0);
            SetFlag(Flag::C, m_Registers.Single[*CpuRegister::A] < tmp);
            return true;
        }
    case 1:
        tmp = m_Registers.Single[*CpuRegister::A];
        m_Registers.Single[*CpuRegister::A] += bus->GetData();
        SetFlag(Flag::Z, m_Registers.Single[*CpuRegister::A] == 0);
        SetFlag(Flag::N, false);
        SetFlag(Flag::H, (m_Registers.Single[*CpuRegister::A] & 0x10) != 0);
        SetFlag(Flag::C, m_Registers.Single[*CpuRegister::A] < tmp);
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::SUB(GBInstructionContext* context,  GBBus* bus)
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
            SetFlag(Flag::H, (m_Registers.Single[*CpuRegister::A] & 0x0F) < (m_Registers.Single[context->GetZ()] & 0x0F));
            m_Registers.Single[*CpuRegister::A] -= m_Registers.Single[context->GetZ()];
            SetFlag(Flag::Z, m_Registers.Single[*CpuRegister::A] == 0);
            SetFlag(Flag::N, true);
            SetFlag(Flag::C, (m_Registers.Single[*CpuRegister::A] & 0x80) == 0);
            return true;
        }
    case 1:
        SetFlag(Flag::H, (m_Registers.Single[*CpuRegister::A] & 0x0F) < (bus->GetData() & 0x0F));
        m_Registers.Single[*CpuRegister::A] -= bus->GetData();
        SetFlag(Flag::Z, m_Registers.Single[*CpuRegister::A] == 0);
        SetFlag(Flag::N, true);
        SetFlag(Flag::C, (m_Registers.Single[*CpuRegister::A] & 0x80) == 0);
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
            SetFlag(Flag::Z, m_Registers.Single[*CpuRegister::A] == m_Registers.Single[context->GetZ()]);
            SetFlag(Flag::N, true);
            SetFlag(Flag::H, (m_Registers.Single[*CpuRegister::A] & 0x0F) < (m_Registers.Single[context->GetZ()] & 0x0F));
            SetFlag(Flag::C, m_Registers.Single[*CpuRegister::A] < m_Registers.Single[context->GetZ()]);
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
        if (context->GetY() == *CpuRegister::F)
        {
            bus->SetAddress(m_Registers.Double[*CpuRegister::HL]);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
        else
        {
            m_Registers.Single[context->GetY()]++;
            SetFlag(Flag::Z, m_Registers.Single[context->GetY()] == 0);
            SetFlag(Flag::N, false);
            SetFlag(Flag::H, (m_Registers.Single[context->GetY()] & 0x0F) == 0);
            return true;
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
    Q_UNUSED(bus)
    switch (context->GetStep())
    {
    case 0:
        if (context->GetW() == *CpuRegister::AF)
        {
            context->SetCarry((m_SP & 0x00FF) == 0xFF);
            m_SP = (m_SP & 0xFF00) | ((m_SP + 1) & 0x00FF);
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

bool GBCpu::DEC_r(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        if (context->GetY() == *CpuRegister::F)
        {
            bus->SetAddress(m_Registers.Double[*CpuRegister::HL]);
            bus->RequestRead();
            context->AdvanceStep();
            return false;
        }
        else
        {
            m_Registers.Single[context->GetY()]--;
            SetFlag(Flag::Z, m_Registers.Single[context->GetY()] == 0);
            SetFlag(Flag::N, false);
            SetFlag(Flag::H, (m_Registers.Single[context->GetY()] & 0x0F) != 0x0F);
            return true;
        }
    case 1:
        //no need to set address, it is the same of previous step
        bus->SetData(bus->GetData() - 1);
        SetFlag(Flag::Z, bus->GetData() == 0);
        SetFlag(Flag::N, false);
        SetFlag(Flag::H, (bus->GetData() & 0x0F) != 0x0F);
        context->AdvanceStep();
        return false;
    case 2:
        bus->RequestWrite();
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

bool GBCpu::LDI(GBInstructionContext* context, GBBus* bus)
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
        m_Registers.Double[*CpuRegister::HL] += 1;
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
        if (!context->GetBit(Bit::Bit0))
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
        bus->SetAddress(--m_SP);
        bus->SetData(static_cast<quint8>((m_PC & 0xFF00) >> 8));
        bus->RequestWrite();
        context->AdvanceStep();
        return false;
    case 4:
        bus->SetAddress(--m_SP);
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

bool GBCpu::RET(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        //Check if condition is specified
        if (!context->GetBit(Bit::Bit0))
        {
            bool exec;
            switch (static_cast<Condition>(context->GetQ()))
            {
            case Condition::Z:
                exec = GetFlag(Flag::Z);
                break;
            case Condition::NZ:
                exec = !GetFlag(Flag::Z);
                break;
            case Condition::C:
                exec = GetFlag(Flag::C);
                break;
            case Condition::NC:
                exec = !GetFlag(Flag::C);
                break;
            }
            //Use the internal carry to store the information about condition
            context->SetCarry(exec);
        }
        else
        {
            //No condition required, read data from stack
            bus->SetAddress(m_SP++);
            bus->RequestRead();
        }
        context->AdvanceStep();
        return false;
    case 1:
        //Check if condition is specified
        if (!context->GetBit(Bit::Bit0))
        {
            if (context->GetCarry())
            {
                //read data from stack
                bus->SetAddress(m_SP++);
                bus->RequestRead();
            }
            else
            {
                //condition not satisfied, complete execution
                return true;
            }
        }
        else
        {
            context->SetLSB(bus->GetData());
            bus->SetAddress(m_SP++);
            bus->RequestRead();
        }
        context->AdvanceStep();
        return false;
    case 2:
        //Check if condition is specified
        if (!context->GetBit(Bit::Bit0))
        {
            context->SetLSB(bus->GetData());
            bus->SetAddress(m_SP++);
            bus->RequestRead();
        }
        else
        {
            context->SetMSB(bus->GetData());
        }
        context->AdvanceStep();
        return false;
    case 3:
        //Check if condition is specified
        if (!context->GetBit(Bit::Bit0))
        {
            context->SetMSB(bus->GetData());
            context->AdvanceStep();
            return false;
        }
        else
        {
            m_PC = context->Get16BitData();
            return true;
        }
    case 4:
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

bool GBCpu::RL(GBInstructionContext* context, GBBus* bus)
{
    switch (context->GetStep())
    {
    case 0:
        if (context->GetZ() == *CpuRegister::F)
        {
            bus->SetAddress(m_Registers.Double[*CpuRegister::HL]);
            bus->RequestRead();
        }
        else
        {
            context->SetCarry((m_Registers.Single[context->GetZ()] & 0x80) != 0);
        }
        context->AdvanceStep();
        return false;
    case 1:
        if (context->GetZ() == *CpuRegister::F)
        {
            context->SetCarry((bus->GetData() & 0x80) != 0);
            context->SetLSB(bus->GetData());
            context->AdvanceStep();
            return false;
        }
        else
        {
            m_Registers.Single[context->GetZ()] = (m_Registers.Single[context->GetZ()] << 1) & 0xFF;
            SetFlag(Flag::Z, m_Registers.Single[context->GetZ()] == 0);
            SetFlag(Flag::N, false);
            SetFlag(Flag::H, false);
            SetFlag(Flag::C, context->GetCarry());
            return true;
        }
    case 2:
        bus->SetData((context->Get8BitData() << 1) & 0xFF);
        SetFlag(Flag::Z, bus->GetData() == 0);
        SetFlag(Flag::N, false);
        SetFlag(Flag::H, false);
        SetFlag(Flag::C, context->GetCarry());
        context->AdvanceStep();
        return false;
    case 3:
        bus->RequestWrite();
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}

bool GBCpu::RLA(GBInstructionContext* context, GBBus* bus)
{
    Q_UNUSED(bus)
    switch (context->GetStep())
    {
    case 0:
        SetFlag(Flag::N, false);
        SetFlag(Flag::H, false);
        SetFlag(Flag::C, (m_Registers.Single[*CpuRegister::A] & 0x80) != 0);
        m_Registers.Single[*CpuRegister::A] = (m_Registers.Single[*CpuRegister::A] << 1) & 0xFF;
        SetFlag(Flag::Z, m_Registers.Single[*CpuRegister::A] == 0);
        return true;
    }
    m_ErrorCode = Error::CPU_UnespectedOpCodeStep;
    return true;
}
