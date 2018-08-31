#include "GBCpu.h"

GBCpu::Instruction GBCpu::s_InstructionTable[2][INSTRUCTIONS_NUM] = { { nullptr } };

bool GBCpu::s_IsInstructionTableInitialized = false;

void GBCpu::InitializeInstructionTable()
{
    //prepare function pointers
    Instruction methods[Instructions::TOTAL];
    methods[Instructions::NOP] = std::bind(&GBCpu::NOP, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::LD_16BIT] = std::bind(&GBCpu::LD_16Bit, std::placeholders::_1, std::placeholders::_2);
    methods[Instructions::XOR] = std::bind(&GBCpu::XOR, std::placeholders::_1, std::placeholders::_2);
    //assign function pointers for standard set
    for (int opCode = 0; opCode < INSTRUCTIONS_NUM; opCode++)
    {
        switch (opCode)
        {
        case 0x00:
            s_InstructionTable[0][opCode] = methods[Instructions::NOP];
            break;
        case 0x01:
        case 0x11:
        case 0x21:
        case 0x31:
            s_InstructionTable[0][opCode] = methods[Instructions::LD_16BIT];
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
            s_InstructionTable[0][opCode] = methods[Instructions::XOR];
            break;
        }
    }
    //assign function pointers for CB set
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
        inst = s_InstructionTable[1][rawOpCode];
    }
    else
    {
        inst = s_InstructionTable[0][rawOpCode];
    }
    //execute the instruction
    if (inst != nullptr)
    {
        inst(this, OpCode(rawOpCode));
#ifdef DEBUG
        qDebug("Op code 0x%x executed", rawOpCode);
#endif
    }
    else
    {
        m_ErrorCode = 1; //TODO put proper error code
#ifdef DEBUG
        qDebug("Op code 0x%x not implemented", rawOpCode);
#endif
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
    if (opCode.GetW() == REG_SP)
    {
        m_SP = value;
    }
    else
    {
        m_Registers.Double[opCode.GetW()] = value;
    }
}

void GBCpu::XOR(OpCode opCode)
{
    quint8 value = 0;
    m_Cycles++;
    //check if value has to be read from memory
    if (opCode.GetZ() == FROM_HL)
    {
        m_Cycles++;
        if(opCode.GetX() == 0b11)
        {
            value = m_Memory->ReadByte(m_PC++);
        }
        else
        {
            value = m_Memory->ReadByte(m_Registers.Double[REG_HL]);
        }
    }
    else
    {
        value = m_Registers.Single[opCode.GetZ()];
    }
    m_Registers.Single[REG_A] ^= value;
    //set flags
    ResetFlag(FlagMasks::All);
    if (m_Registers.Single[REG_A] == 0)
    {
        SetFlag(FlagMasks::Z);
    }
}
