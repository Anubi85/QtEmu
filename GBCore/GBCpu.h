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

enum class FlagMasks : quint8
{
    C = 0x10,
    H = 0x20,
    N = 0x40,
    Z = 0x80,
    All = 0xF0
};

//maintanins the explicit conversion to int but provides a sort of "scope" support
namespace Conditions
{
    enum
    {
        NZ = 0x00,
        Z = 0x01,
        NC = 0x02,
        C = 0x03
    };
}

//maintanins the explicit conversion to int but provides a sort of "scope" support
namespace Registers
{
    enum
    {
        B = 0x00,
        C = 0x01,
        D = 0x02,
        E = 0x03,
        H = 0x04,
        L = 0x05,
        F = 0x06,
        A = 0x07,
        ADR_HL = 0x06,
        BC = 0x00,
        DE = 0x01,
        HL = 0x02,
        AF = 0x03,
        SP = 0x03
    };
}

//maintanins the explicit conversion to int but provides a sort of "scope" support
namespace Instructions
{
    enum
    {
        NOP,
        LD_8BIT,
        LD_16BIT,
        LDD,
        XOR,
        INC,
        BIT,
        RL,
        JR,
        CALL,
        PUSH,
        TOTAL
    };
}

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
    bool GetFlag(FlagMasks flagMask) { return (m_Registers.Single[Registers::F] & static_cast<quint8>(flagMask)) != 0; }
    //Instructions
    void NOP(OpCode opCode);
    void LD_8Bit(OpCode opCode);
    void LD_16Bit(OpCode opCode);
    void LDD(OpCode opCode);
    void XOR(OpCode opCode);
    void INC(OpCode opCode);
    void BIT(OpCode opCode);
    void RL(OpCode opCode);
    void JR(OpCode opCode);
    void CALL(OpCode opCode);
    void PUSH(OpCode opCode);
public:
    GBCpu(GBMemory* memory);
    void Reset();
    void Exec();
    bool HasError() { return m_ErrorCode != 0; }
};

#endif // GBCPU_H
