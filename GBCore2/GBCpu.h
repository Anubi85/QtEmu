#ifndef GBCPU_H
#define GBCPU_H

#include <QtCore>
#include "GBComponent.h"
#include "GBUtils.h"

#define REG8_NUM 8
#define REG16_NUM 4
#define INSTRUCTIONS_NUM 256

enum class FlagMask : quint8
{
    C = 0x10,
    H = 0x20,
    N = 0x40,
    Z = 0x80
};

enum class Condition
{
    NZ = 0x00,
    Z  = 0x01,
    NC = 0x02,
    C  = 0x03
};

enum class Register
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

//Forward class declarations
class GBInstructionContext;
class IGBCpuState;
class GBCpuState_Fetch;
class GBCpuState_CBFetch;
class GBCpuState_Decode;

class GBCpu : public GBComponent
{
    friend GBCpuState_Fetch;
    friend GBCpuState_CBFetch;
    friend GBCpuState_Decode;
private:
    typedef void (GBCpu::*Instruction)(GBInstructionContext*);

    static Instruction s_InstructionTable[INSTRUCTIONS_NUM];
    static Instruction s_CBInstructionTable[INSTRUCTIONS_NUM];

    quint64 m_Cycles;
    quint16 m_PC;
    quint16 m_SP;
    union
    {
        long long All;
        quint8 Single[REG8_NUM];
        quint16_be Double[REG16_NUM];
    } m_Registers;
    IGBCpuState* m_State;

    void SetState(IGBCpuState* newState);
    void SetFlag(FlagMask flagMask, bool value);
    bool GetFlag(FlagMask flagMask) { return (m_Registers.Single[*Register::F] & *flagMask) != 0; }
public:
    GBCpu();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBCPU_H
