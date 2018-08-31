#ifndef GBCPU_H
#define GBCPU_H

#include <QtCore>
#include <functional>
#include "OpCode.h"
#include "GBMemory.h"

#define REG8_NUM 8
#define REG16_NUM 4
#define REG_F 0x06
#define FROM_HL REG_F

enum FlagMasks : quint8
{
    C = 0x10,
    H = 0x20,
    N = 0x40,
    Z = 0x80
};

typedef std::function<void(OpCode)> Instruction;

class GBCpu
{
private:
    GBMemory* m_Memory;
    quint16 m_PC;
    quint16 m_SP;
    quint64 m_Cycles;
    union
    {
        long long All;
        quint8 Single[REG8_NUM];
        quint16 Double[REG16_NUM];
    } m_Registers;
    void SetFlag(FlagMasks flagMask) { m_Registers.Single[REG_F] |= flagMask; }
    void ResetFlag(FlagMasks flagMask) { m_Registers.Single[REG_F] &= ~flagMask; }
    OpCode Fetch();
    Instruction Decode();
public:
    GBCpu(GBMemory* memory);
    void Reset();
    void Exec();
};

#endif // GBCPU_H
