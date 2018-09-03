#ifndef GBCPU_H
#define GBCPU_H

#include <QtCore>
#include <functional>
#include "OpCode.h"
#include "GBMemory.h"

#define REG8_NUM 8
#define REG16_NUM 4
#define INSTRUCTIONS_NUM 256
#define INSTRUCTIONS_SETS 2
#define REGULAR 0
#define EXTENDED 1

enum FlagMasks
{
    FLAG_C = 0x10,
    FLAG_H = 0x20,
    FLAG_N = 0x40,
    FLAG_Z = 0x80,
    FLAG_All = 0xF0
};

enum Conditions
{
    COND_NZ = 0x00,
    COND_Z = 0x01,
    COND_NC = 0x02,
    COND_C = 0x03
};

enum Registers
{
    REG_B = 0x00,
    REG_C = 0x01,
    REG_D = 0x02,
    REG_E = 0x03,
    REG_H = 0x04,
    REG_L = 0x05,
    REG_F = 0x06,
    REG_A = 0x07,
    ADR_HL = 0x06,
    REG_BC = 0x00,
    REG_DE = 0x01,
    REG_HL = 0x02,
    REG_FA = 0x03,
    REG_SP = 0x03
};

enum Instructions
{
    NOP,
    LD_16BIT,
    LDD,
    XOR,
    BIT,
    JR,
    TOTAL
};

class GBCpu
{
private:
    typedef std::function<void(GBCpu*, OpCode)> Instruction;

    static Instruction s_InstructionTable[INSTRUCTIONS_SETS][INSTRUCTIONS_NUM];
    static bool s_IsInstructionTableInitialized;
    static void InitializeInstructionTable();

    GBMemory* m_Memory;
    quint32 m_ErrorCode;
    quint64 m_Cycles;    
    quint16 m_PC;
    quint16 m_SP;
    union
    {
        long long All;
        quint8 Single[REG8_NUM];
        quint16 Double[REG16_NUM];
    } m_Registers;

    void SetFlag(FlagMasks flagMask, bool value);
    bool GetFlag(FlagMasks flagMask) { return (m_Registers.Single[Registers::REG_F] & flagMask) != 0; }
    //Instructions
    void NOP(OpCode opCode);
    void LD_16Bit(OpCode opCode);
    void LDD(OpCode opCode);
    void XOR(OpCode opCode);
    void BIT(OpCode opCode);
    void JR(OpCode opCode);
public:
    GBCpu(GBMemory* memory);
    void Reset();
    void Exec();
    bool HasError() { return m_ErrorCode != 0; }
};

#endif // GBCPU_H
