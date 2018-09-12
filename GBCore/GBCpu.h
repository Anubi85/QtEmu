#ifndef GBCPU_H
#define GBCPU_H

#include <QtCore>
#include <functional>
#include "GBOpCode.h"
#include "GBComponent.h"
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
    Z = 0x80
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

class GBCpu : public GBComponent
{
private:
    typedef void (GBCpu::*Instruction)(GBOpCode);

    static Instruction s_InstructionTable[INSTRUCTIONS_SETS][INSTRUCTIONS_NUM];

    GBMemory* m_Memory;
    quint64 m_Cycles;    
    quint16 m_PC;
    quint16 m_SP;
    union
    {
        long long All;
        quint8 Single[REG8_NUM];
        quint16_be Double[REG16_NUM];
    } m_Registers;

    void Exec(Instruction inst, quint8 rawOpCode) { (this->*inst)(GBOpCode(rawOpCode)); }
    void SetFlag(FlagMasks flagMask, bool value);
    bool GetFlag(FlagMasks flagMask) { return (m_Registers.Single[Registers::F] & static_cast<quint8>(flagMask)) != 0; }
    //Instructions
    void NOP(GBOpCode opCode);
    void LD_8Bit(GBOpCode opCode);
    void LD_16Bit(GBOpCode opCode);
    void LDD(GBOpCode opCode);
    void LDI(GBOpCode opCode);
    void XOR(GBOpCode opCode);
    void CP(GBOpCode opCode);
    void INC_8Bit(GBOpCode opCode);
    void DEC_8Bit(GBOpCode opCode);
    void INC_16Bit(GBOpCode opCode);
    void BIT(GBOpCode opCode);
    void RL(GBOpCode opCode);
    void JR(GBOpCode opCode);
    void CALL(GBOpCode opCode);
    void RET(GBOpCode opCode);
    void PUSH(GBOpCode opCode);
    void POP(GBOpCode opCode);
public:
    GBCpu(GBMemory* memory);
    void Reset() override;
    void Exec();
};

#endif // GBCPU_H
