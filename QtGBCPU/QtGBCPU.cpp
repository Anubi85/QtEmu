#include "QtGBCPU.h"

QtGBCPU::QtGBCPU()
{
    m_Memory = IQtGBMemory::GetInstance();
    //clear the registers
    Reset();
    //initialize instructions array
    for (int i = 0; i < INSTRUCTION_NUM; i++)
    {
        m_Instructions[i] = nullptr;
    }
    m_Instructions[0x00] = std::bind(&QtGBCPU::NOP, this);
    m_Instructions[0x31] = std::bind(&QtGBCPU::LD_SP_nn, this);
    m_Instructions[0xAF] = std::bind(&QtGBCPU::XOR_A, this);
}

void QtGBCPU::Reset()
{
    m_ErrorOccurred = false;
    m_Registers.All = 0;
    m_PC = 0;
    m_SP = 0;
}

void QtGBCPU::Exec()
{
    ushort opCode = m_Memory->ReadByte(m_PC++);
    //execure instruction
    Instruction inst = m_Instructions[opCode];
    if (inst != nullptr)
    {
        inst();
    }
    else
    {
        m_ErrorOccurred = true;
#ifdef DEBUG
        qDebug("Op code 0x%x not implemented", opCode);
#endif
    }
}

void QtGBCPU::LD_SP_nn()
{
    m_SP = m_Memory->ReadWord(m_PC);
    m_PC += 2;
}

void QtGBCPU::XOR_A()
{
    m_Registers.Single.A = m_Registers.Single.A ^ m_Registers.Single.A;
    m_Registers.Single.F = 0;
    m_Registers.Flags.Z = m_Registers.Single.A == 0;
}
