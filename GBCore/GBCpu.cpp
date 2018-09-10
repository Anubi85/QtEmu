#include "GBCpu.h"

GBCpu::GBCpu(GBMemory* memory)
{
    m_Memory = memory;
    Reset();
}

void GBCpu::Reset()
{
    GBComponent::Reset();
    m_Cycles = 0;
    m_PC = 0;
    m_SP = 0;
    m_Registers.All = 0;
    if (m_Memory != nullptr)
    {
        m_Memory->Reset();
    }
}

void GBCpu::Exec()
{
    Instruction inst = nullptr;
    //fetch the instruction from memory
    quint8 rawOpCode = m_Memory->ReadByte(m_PC++);
    //decode the intruction
    if (rawOpCode == 0xCB)
    {
        rawOpCode = m_Memory ->ReadByte(m_PC++);
#ifdef DEBUG
        qDebug("Extended");
#endif
        inst = s_InstructionTable[EXTENDED][rawOpCode];
    }
    else
    {
        inst = s_InstructionTable[REGULAR][rawOpCode];
    }
    //execute the instruction
    if (inst != nullptr)
    {
        Exec(inst, rawOpCode);
#ifdef DEBUG
        qDebug("Op code 0x%02X executed", rawOpCode);
#endif
    }
    else
    {
        m_ErrorCode = 1; //TODO put proper error code
#ifdef DEBUG
        qDebug("Op code 0x%02X not implemented", rawOpCode);
#endif
    }
    //tutto ok fino a  PC = 0x0064, implementare V-Blank e IO
}

void GBCpu::SetFlag(FlagMasks flagMask, bool value)
{
    if (value)
    {
        m_Registers.Single[Registers::F] |= static_cast<quint8>(flagMask);
    }
    else
    {
        m_Registers.Single[Registers::F] &= ~static_cast<quint8>(flagMask);
    }
}

void GBCpu::NOP(OpCode opCode)
{
    m_Cycles++;
}

void GBCpu::LD_16Bit(OpCode opCode)
{
    m_Cycles += 3;
    //get value from memory
    quint16 value = m_Memory->ReadWord(m_PC);
    m_PC += 2;
    if (opCode.GetW() == Registers::SP)
    {
        m_SP = value;
    }
    else
    {
        m_Registers.Double[opCode.GetW()] = value;
    }
}

void GBCpu::LDD(OpCode opCode)
{
    m_Cycles += 2;
    if (opCode.GetF())
    {
        m_Registers.Single[Registers::A] = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
    }
    else
    {
        m_Memory->WriteByte(m_Registers.Double[Registers::HL], m_Registers.Single[Registers::A]);
    }
    m_Registers.Double[Registers::HL] -= 1;
}

void GBCpu::LDI(OpCode opCode)
{
    m_Cycles += 2;
    if (opCode.GetF())
    {
        m_Registers.Single[Registers::A] = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
    }
    else
    {
        m_Memory->WriteByte(m_Registers.Double[Registers::HL], m_Registers.Single[Registers::A]);
    }
    m_Registers.Double[Registers::HL] += 1;
}

void GBCpu::XOR(OpCode opCode)
{
    quint8 value = 0;
    m_Cycles++;
    //check if value has to be read from memory
    if (opCode.GetZ() == Registers::ADR_HL)
    {
        m_Cycles++;
        if(opCode.GetX() == 0b11)
        {
            value = m_Memory->ReadByte(m_PC++);
        }
        else
        {
            value = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
        }
    }
    else
    {
        value = m_Registers.Single[opCode.GetZ()];
    }
    m_Registers.Single[Registers::A] ^= value;
    //set flags
    SetFlag(FlagMasks::Z, m_Registers.Single[Registers::A] == 0);
    SetFlag(FlagMasks::N, false);
    SetFlag(FlagMasks::C, false);
    SetFlag(FlagMasks::H, false);
}

void GBCpu::BIT(OpCode opCode)
{
    m_Cycles += 2;
    quint8 toTest = 0;
    if (opCode.GetZ() == Registers::ADR_HL)
    {
        m_Cycles += 2;
        toTest = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
        m_PC += 2;
    }
    else
    {
        toTest = m_Registers.Single[opCode.GetZ()];
    }
    SetFlag(FlagMasks::Z, (toTest & (1 << opCode.GetY())) == 0);
    SetFlag(FlagMasks::H, true);
    SetFlag(FlagMasks::N, false);
}

void GBCpu::JR(OpCode opCode)
{
    m_Cycles += 2;
    bool jump = true;
    //check if conditional jump
    if (opCode.GetG())
    {
        //check condition
        switch (opCode.GetQ())
        {
        case Conditions::Z:
            jump = GetFlag(FlagMasks::Z);
            break;
        case Conditions::NZ:
            jump = !GetFlag(FlagMasks::Z);
            break;
        case Conditions::C:
            jump = GetFlag(FlagMasks::C);
            break;
        case Conditions::NC:
            jump = !GetFlag(FlagMasks::C);
            break;
        }
    }
    if (jump)
    {
        qint8 toJump = static_cast<qint8>(m_Memory->ReadByte(m_PC++));
        m_PC += toJump;
    }
    else
    {
        //skip the value in memory
        m_PC++;
    }
}

void GBCpu::LD_8Bit(OpCode opCode)
{
    m_Cycles++;
    quint8 value = 0;
    switch (opCode.GetX())
    {
    case 0b00:
        m_Cycles++;
        switch (opCode.GetZ())
        {
        case 0b010:
            //special case, write is performed here and then the method returns
            if (opCode.GetF())
            {
                m_Registers.Single[Registers::A] = m_Memory->ReadByte(m_Registers.Double[opCode.GetW()]);
            }
            else
            {
                m_Memory->WriteByte(m_Registers.Double[opCode.GetW()], m_Registers.Single[Registers::A]);
            }
            return;
        case 0b110:
            value = m_Memory->ReadByte(m_PC++);
            break;
        }
        break;
    case 0b01:
        if (opCode.GetZ() == Registers::ADR_HL)
        {
            m_Cycles++;
            value = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
        }
        else
        {
            value = m_Registers.Single[opCode.GetZ()];
        }
        break;
    case 0b11:
        //special case, write is performed here and then the method returns
        quint16 address = 0;
        switch (opCode.GetZ())
        {
        case 0b000:
            m_Cycles += 2;
            address = 0xFF00 | m_Memory->ReadByte(m_PC++);
            break;
        case 0b010:
            m_Cycles++;
            if (opCode.GetF())
            {
                m_Cycles += 2;
                address = m_Memory->ReadWord(m_PC);
                m_PC += 2;
            }
            else
            {
                address = 0xFF00 | m_Registers.Single[Registers::C];
            }
            break;
        }
        switch (opCode.GetW())
        {
        case 0b10:
            m_Memory->WriteByte(address, m_Registers.Single[Registers::A]);
            break;
        case 0b11:
            m_Registers.Single[Registers::A] = m_Memory->ReadByte(address);
            break;
        }
        return;
    }
    if (opCode.GetY() == Registers::ADR_HL)
    {
        m_Cycles++;
        m_Memory->WriteByte(m_Registers.Double[Registers::HL], value);
    }
    else
    {
        m_Registers.Single[opCode.GetY()] = value;
    }
}

void GBCpu::INC_8Bit(OpCode opCode)
{
    m_Cycles++;
    quint8 finalValue;
    if (opCode.GetY() == Registers::ADR_HL)
    {
        m_Cycles += 2;
        finalValue = m_Memory->ReadByte(m_Registers.Double[Registers::HL]) + 1;
        m_Memory->WriteByte(m_Registers.Double[Registers::HL], finalValue);
    }
    else
    {
        finalValue = m_Registers.Single[opCode.GetY()] + 1;
        m_Registers.Single[opCode.GetY()] = finalValue;
    }
    SetFlag(FlagMasks::Z, finalValue == 0);
    SetFlag(FlagMasks::N, false);
    SetFlag(FlagMasks::H, (finalValue & 0x0F) == 0);
}

void GBCpu::DEC_8Bit(OpCode opCode)
{
    m_Cycles++;
    quint8 finalValue;
    if (opCode.GetY() == Registers::ADR_HL)
    {
        m_Cycles += 2;
        finalValue = m_Memory->ReadByte(m_Registers.Double[Registers::HL]) - 1;
        m_Memory->WriteByte(m_Registers.Double[Registers::HL], finalValue);
    }
    else
    {
        finalValue = m_Registers.Single[opCode.GetY()] - 1;
        m_Registers.Single[opCode.GetY()] = finalValue;
    }
    SetFlag(FlagMasks::Z, finalValue == 0);
    SetFlag(FlagMasks::N, true);
    SetFlag(FlagMasks::H, (finalValue & 0x0F) == 0);
}

void GBCpu::INC_16Bit(OpCode opCode)
{
    m_Cycles++;
    if (opCode.GetW() == Registers::SP)
    {
        m_SP++;
    }
    else
    {
        m_Registers.Double[opCode.GetW()] += 1;
    }
}

void GBCpu::CALL(OpCode opCode)
{
    m_Cycles += 3;
    bool execute = true;
    if (opCode.GetZ() == 0b100)
    {
        switch (opCode.GetQ())
        {
        case Conditions::Z:
            execute = GetFlag(FlagMasks::Z);
            break;
        case Conditions::NZ:
            execute = !GetFlag(FlagMasks::Z);
            break;
        case Conditions::C:
            execute = GetFlag(FlagMasks::C);
            break;
        case Conditions::NC:
            execute = !GetFlag(FlagMasks::C);
            break;
        }
    }
    if (execute)
    {
        quint16 address = m_Memory->ReadWord(m_PC);
        m_PC += 2;
        m_SP--;
        m_Memory->WriteWord(m_SP--, m_PC);
        m_PC = address;
    }
    else
    {
        m_PC += 2;
    }
}

void GBCpu::RET(OpCode opCode)
{
    m_Cycles += 2;
    bool execute = true;
    bool activateInterrupts = false;
    if (opCode.GetZ() == 0b000)
    {
        switch (opCode.GetQ())
        {
        case Conditions::Z:
            execute = GetFlag(FlagMasks::Z);
            break;
        case Conditions::NZ:
            execute = !GetFlag(FlagMasks::Z);
            break;
        case Conditions::C:
            execute = GetFlag(FlagMasks::C);
            break;
        case Conditions::NC:
            execute = !GetFlag(FlagMasks::C);
            break;
        }
    }
    else
    {
        activateInterrupts = opCode.GetW() == 0b01;
    }
    if (execute)
    {
        m_SP++;
        m_PC = m_Memory->ReadWord(m_SP++);
        if (activateInterrupts)
        {
            m_Memory->WriteByte(0xFFFF, 0x1F);
        }
    }
}

void GBCpu::PUSH(OpCode opCode)
{
    m_Cycles += 4;
    m_SP--;
    m_Memory->WriteWord(m_SP--, m_Registers.Double[opCode.GetW()]);
}

void GBCpu::POP(OpCode opCode)
{
    m_Cycles += 3;
    m_SP++;
    m_Registers.Double[opCode.GetW()] = m_Memory->ReadWord(m_SP++);
}

void GBCpu::RL(OpCode opCode)
{
    m_Cycles += 2;
    quint8 value;
    if (opCode.GetZ() == Registers::ADR_HL)
    {
        m_Cycles += 2;
        value = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
        m_Memory ->WriteByte(m_Registers.Double[Registers::HL], (value << 1) & 0xFF);
    }
    else
    {
        value = m_Registers.Single[opCode.GetZ()];
        m_Registers.Single[opCode.GetZ()] = (value << 1) & 0xFF;
    }
    SetFlag(FlagMasks::Z, value == 0x80);
    SetFlag(FlagMasks::N, false);
    SetFlag(FlagMasks::H, false);
    SetFlag(FlagMasks::C, (value & 0x80) != 0);
}

void GBCpu::CP(OpCode opCode)
{
    quint8 value = 0;
    m_Cycles++;
    //check if value has to be read from memory
    if (opCode.GetZ() == Registers::ADR_HL)
    {
        m_Cycles++;
        if(opCode.GetX() == 0b11)
        {
            value = m_Memory->ReadByte(m_PC++);
        }
        else
        {
            value = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
        }
    }
    else
    {
        value = m_Registers.Single[opCode.GetZ()];
    }
    //set flags
    SetFlag(FlagMasks::Z, m_Registers.Single[Registers::A] == value);
    SetFlag(FlagMasks::N, true);
    SetFlag(FlagMasks::C, m_Registers.Single[Registers::A] < value);
    SetFlag(FlagMasks::H, (m_Registers.Single[Registers::A] & 0x0F) < (value & 0x0F));
}
