#ifndef GBCPU_H
#define GBCPU_H

#include <QtCore>
#include <functional>
#include "OpCode.h"
#include "GBMemory.h"

#define REG8_NUM 8
#define REG16_NUM 4
#define REG_A 0x07
#define REG_F 0x06
#define REG_SP 0x03
#define REG_HL 0x02
#define FROM_HL REG_F
#define INSTRUCTIONS_NUM 256

enum FlagMasks : quint8
{
    C = 0x10,
    H = 0x20,
    N = 0x40,
    Z = 0x80,
    All = 0xF0
};

enum Instructions
{
    NOP,
    LD_16BIT,
    XOR,
    TOTAL
};

class GBCpu
{
private:
    typedef std::function<void(GBCpu*, OpCode)> Instruction;

    static Instruction s_InstructionTable[2][INSTRUCTIONS_NUM];
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

    void SetFlag(FlagMasks flagMask) { m_Registers.Single[REG_F] |= flagMask; }
    void ResetFlag(FlagMasks flagMask) { m_Registers.Single[REG_F] &= ~flagMask; }
    //Instructions
    void NOP(OpCode opCode);
    void LD_16Bit(OpCode opCode);
    void XOR(OpCode opCode);
public:
    GBCpu(GBMemory* memory);
    void Reset();
    void Exec();
    bool HasError() { return m_ErrorCode != 0; }
};

#endif // GBCPU_H
