#ifndef GBCPU_H
#define GBCPU_H

#include <QtCore>
#include "GBComponent.h"

#define REG8_NUM 8
#define REG16_NUM 4
#define INSTRUCTIONS_NUM 256

//maintanins the explicit conversion to int but provides a sort of "scope" support
namespace InstructionSets
{
    enum
    {
        REGULAR = 0,
        EXTENDED = 1,
        ALL = 2
    };
}


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
        Z  = 0x01,
        NC = 0x02,
        C  = 0x03
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

class GBInstructionContext
{
public:
    GBInstructionContext();
};

class IGBCpuState;
class GBCpuState_Fetch;

class GBCpu : public GBComponent
{
    friend GBCpuState_Fetch;
private:
    typedef void (GBCpu::*Instruction)(GBInstructionContext);

    static Instruction s_InstructionTable[InstructionSets::ALL][INSTRUCTIONS_NUM];

    quint64 m_Cycles;
    quint16 m_PC;
    quint16 m_SP;
    union
    {
        long long All;
        quint8 Single[REG8_NUM];
        quint16_be Double[REG16_NUM];
    } m_Registers;
    quint8 m_SkipCounter;
    IGBCpuState* m_State;

    void SetState(IGBCpuState* newState) { m_State = newState; }
    void SetFlag(FlagMasks flagMask, bool value);
    bool GetFlag(FlagMasks flagMask) { return (m_Registers.Single[Registers::F] & static_cast<quint8>(flagMask)) != 0; }
public:
    GBCpu();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBCPU_H
