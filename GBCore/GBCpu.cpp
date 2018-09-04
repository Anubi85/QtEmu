#include "GBCpu.h"

GBCpu::Instruction GBCpu::s_InstructionTable[INSTRUCTIONS_SETS][INSTRUCTIONS_NUM] = { { nullptr } };

bool GBCpu::s_IsInstructionTableInitialized = false;

void GBCpu::InitializeInstructionTable()
{
    //prepare function pointers
    Instruction methods[Instructions::TOTAL];
    methods[Instructions::NOP] = std::bind(&GBCpu::NOP, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::LD_8BIT] = std::bind(&GBCpu::LD_8Bit, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::LD_16BIT] = std::bind(&GBCpu::LD_16Bit, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::LDD] = std::bind(&GBCpu::LDD, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::XOR] = std::bind(&GBCpu::XOR, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::INC] = std::bind(&GBCpu::INC, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::BIT] = std::bind(&GBCpu::BIT, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::JR] = std::bind(&GBCpu::JR, std::placeholders::_1, std::placeholders::_2);
    //assign function pointers for standard set
    for (int opCode = 0; opCode < INSTRUCTIONS_NUM; opCode++)
    {
        switch (opCode)
        {
        case 0x00:
            s_InstructionTable[REGULAR][opCode] = methods[Instructions::NOP];
            break;
        case 0x02:
        case 0x06:
        case 0x0A:
        case 0x0E:
        case 0x12:
        case 0x16:
        case 0x1A:
        case 0x1E:
        case 0x26:
        case 0x2E:
        case 0x36:
        case 0x3E:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x4F:
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
        case 0x55:
        case 0x56:
        case 0x57:
        case 0x58:
        case 0x59:
        case 0x5A:
        case 0x5B:
        case 0x5C:
        case 0x5D:
        case 0x5E:
        case 0x5F:
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65:
        case 0x66:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6A:
        case 0x6B:
        case 0x6C:
        case 0x6D:
        case 0x6E:
        case 0x6F:
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
        case 0x77:
        case 0x78:
        case 0x79:
        case 0x7A:
        case 0x7B:
        case 0x7C:
        case 0x7D:
        case 0x7E:
        case 0x7F:
        case 0xE0:
        case 0xE2:
        case 0xEA:
        case 0xF0:
        case 0xF2:
        case 0xFA:
            s_InstructionTable[REGULAR][opCode] = methods[Instructions::LD_8BIT];
            break;
        case 0x01:
        case 0x11:
        case 0x21:
        case 0x31:
            s_InstructionTable[REGULAR][opCode] = methods[Instructions::LD_16BIT];
            break;
        case 0x18:
        case 0x20:
        case 0x28:
        case 0x30:
        case 0x38:
            s_InstructionTable[REGULAR][opCode] = methods[Instructions::JR];
            break;
        case 0x32:
            s_InstructionTable[REGULAR][opCode] = methods[Instructions::LDD];
            break;
        case 0xA8:
        case 0xA9:
        case 0xAA:
        case 0xAB:
        case 0xAC:
        case 0xAD:
        case 0xAE:
        case 0xAF:
        case 0xEE:
            s_InstructionTable[REGULAR][opCode] = methods[Instructions::XOR];
            break;
        case 0x04:
        case 0x0C:
        case 0x14:
        case 0x1C:
        case 0x24:
        case 0x2C:
        case 0x34:
        case 0x3C:
            s_InstructionTable[REGULAR][opCode] = methods[Instructions::INC];
            break;
        }
    }
    //assign function pointers for CB set
    for (int opCode = 0; opCode < INSTRUCTIONS_NUM; opCode++)
    {
        switch (opCode)
        {
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x4F:
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
        case 0x55:
        case 0x56:
        case 0x57:
        case 0x58:
        case 0x59:
        case 0x5A:
        case 0x5B:
        case 0x5C:
        case 0x5D:
        case 0x5E:
        case 0x5F:
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65:
        case 0x66:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6A:
        case 0x6B:
        case 0x6C:
        case 0x6D:
        case 0x6E:
        case 0x6F:
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
        case 0x76:
        case 0x77:
        case 0x78:
        case 0x79:
        case 0x7A:
        case 0x7B:
        case 0x7C:
        case 0x7D:
        case 0x7E:
        case 0x7F:
            s_InstructionTable[EXTENDED][opCode] = methods[Instructions::BIT];
            break;
        }
    }
    //set initialized flag
    s_IsInstructionTableInitialized = true;
}

GBCpu::GBCpu(GBMemory* memory)
{
    if (!s_IsInstructionTableInitialized)
    {
        InitializeInstructionTable();
    }
    m_Memory = memory;
    Reset();
}

void GBCpu::Reset()
{
    m_ErrorCode = 0;
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
        inst(this, OpCode(rawOpCode));
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
}

void GBCpu::SetFlag(FlagMasks flagMask, bool value)
{
    if (value)
    {
        m_Registers.Single[Registers::REG_F] |= flagMask;
    }
    else
    {
        m_Registers.Single[Registers::REG_F] &= ~flagMask;
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
    if (opCode.GetW() == Registers::REG_SP)
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
    m_Memory->WriteByte(m_Registers.Double[Registers::REG_HL]--, m_Registers.Single[Registers::REG_A]);
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
            value = m_Memory->ReadByte(m_Registers.Double[Registers::REG_HL]);
        }
    }
    else
    {
        value = m_Registers.Single[opCode.GetZ()];
    }
    m_Registers.Single[Registers::REG_A] ^= value;
    //set flags
    SetFlag(FlagMasks::FLAG_All, false);
    if (m_Registers.Single[Registers::REG_A] == 0)
    {
        SetFlag(FlagMasks::FLAG_Z, true);
    }
}

void GBCpu::BIT(OpCode opCode)
{
    m_Cycles += 2;
    quint8 toTest = 0;
    if (opCode.GetZ() == Registers::ADR_HL)
    {
        m_Cycles += 2;
        toTest = m_Memory->ReadByte(m_Registers.Double[Registers::REG_HL]);
        m_PC += 2;
    }
    else
    {
        toTest = m_Registers.Single[opCode.GetZ()];
    }
    SetFlag(FlagMasks::FLAG_Z, toTest & (1 << opCode.GetY()));
    SetFlag(FlagMasks::FLAG_H, true);
    SetFlag(FlagMasks::FLAG_N, false);
}

void GBCpu::JR(OpCode opCode)
{
    m_Cycles += 2;
    qint8 toJump = 0;
    bool jump = true;
    //check if conditional jump
    if (opCode.GetG())
    {
        //check condition
        switch (opCode.GetQ())
        {
        case Conditions::COND_Z:
            jump = GetFlag(FlagMasks::FLAG_Z);
            break;
        case Conditions::COND_NZ:
            jump = !GetFlag(FlagMasks::FLAG_Z);
            break;
        case Conditions::COND_C:
            jump = GetFlag(FlagMasks::FLAG_C);
            break;
        case Conditions::COND_NC:
            jump = !GetFlag(FlagMasks::FLAG_C);
            break;
        }
    }
    if (jump)
    {
        toJump = static_cast<qint8>(m_Memory->ReadByte(m_PC));
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
                m_Registers.Single[Registers::REG_A] = m_Memory->ReadByte(m_Registers.Double[opCode.GetW()]);
            }
            else
            {
                m_Memory->WriteByte(m_Registers.Double[opCode.GetW()], m_Registers.Single[Registers::REG_A]);
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
            value = m_Memory->ReadByte(m_Registers.Double[Registers::REG_HL]);
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
                address = 0xFF00 | m_Registers.Single[Registers::REG_C];
            }
            break;
        }
        switch (opCode.GetW())
        {
        case 0b10:
            m_Memory->WriteByte(address, m_Registers.Single[Registers::REG_A]);
            break;
        case 0b11:
            m_Registers.Single[Registers::REG_A] = m_Memory->ReadByte(address);
            break;
        }
        return;
    }
    if (opCode.GetY() == Registers::ADR_HL)
    {
        m_Cycles++;
        m_Memory->WriteByte(m_Registers.Double[Registers::REG_HL], value);
    }
    else
    {
        m_Registers.Single[opCode.GetY()] = value;
    }
}

void GBCpu::INC(OpCode opCode)
{
    m_Cycles++;
    quint8 finalValue;
    if (opCode.GetY() == Registers::ADR_HL)
    {
        m_Cycles += 2;
        finalValue = m_Memory->ReadByte(m_Registers.Double[Registers::REG_HL]) + 1;
        m_Memory->WriteByte(m_Registers.Double[Registers::REG_HL], finalValue);
    }
    else
    {
        finalValue = m_Registers.Single[opCode.GetY()] + 1;
        m_Registers.Single[opCode.GetY()] = finalValue;
    }
    SetFlag(FlagMasks::FLAG_Z, finalValue == 0);
    SetFlag(FlagMasks::FLAG_N, false);
    SetFlag(FlagMasks::FLAG_H, (finalValue & 0x0F) == 0);
}
