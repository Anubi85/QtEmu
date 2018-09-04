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
    methods[Instructions::RL] = std::bind(&GBCpu::RL, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::JR] = std::bind(&GBCpu::JR, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::CALL] = std::bind(&GBCpu::CALL, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::PUSH] = std::bind(&GBCpu::PUSH, std::placeholders::_1, std::placeholders::_2);
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
        case 0xC4:
        case 0xCC:
        case 0xCD:
        case 0xD4:
        case 0xDC:
            s_InstructionTable[REGULAR][opCode] = methods[Instructions::CALL];
            break;
        case 0xC5:
        case 0xD5:
        case 0xE5:
        case 0xF5:
            s_InstructionTable[REGULAR][opCode] = methods[Instructions::PUSH];
            break;
        case 0x17:
            s_InstructionTable[REGULAR][opCode] = methods[Instructions::RL];
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
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
            s_InstructionTable[EXTENDED][opCode] = methods[Instructions::RL];
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
    m_Memory->WriteByte(m_Registers.Double[Registers::HL]--, m_Registers.Single[Registers::A]);
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
    SetFlag(FlagMasks::All, false);
    if (m_Registers.Single[Registers::A] == 0)
    {
        SetFlag(FlagMasks::Z, true);
    }
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
    SetFlag(FlagMasks::Z, toTest & (1 << opCode.GetY()));
    SetFlag(FlagMasks::H, true);
    SetFlag(FlagMasks::N, false);
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

void GBCpu::INC(OpCode opCode)
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
        m_Memory->WriteWord(m_SP, m_PC);
        m_SP -= 2;
        m_PC = address;
    }
    else
    {
        m_PC += 2;
    }
}

void GBCpu::PUSH(OpCode opCode)
{
    m_Cycles += 4;
    m_Memory->WriteWord(m_SP, m_Registers.Double[opCode.GetW()]);
    m_SP -= 2;
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
