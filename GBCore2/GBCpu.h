#ifndef GBCPU_H
#define GBCPU_H

#include <QtCore>
#include "GBComponent.h"
#include "GBInstruction.h"
#include "GBUtils.h"

#define REG8_NUM 8
#define REG16_NUM 4
#define INSTRUCTIONS_NUM 256

enum class Flag : quint8
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

enum class CpuRegister
{
         B = 0x00,
         C = 0x01,
         D = 0x02,
         E = 0x03,
         H = 0x04,
         L = 0x05,
         F = 0x06,
         A = 0x07,
        BC = 0x00,
        DE = 0x01,
        HL = 0x02,
        AF = 0x03,
};

//Forward class declarations
class IGBCpuState;
class GBCpuState_Fetch;
class GBCpuState_Decode;
class GBCpuState_Execute;
class GBCpuState_InterruptCheck;

class GBCpu : public GBComponent
{
    friend GBCpuState_Fetch;
    friend GBCpuState_Decode;
    friend GBCpuState_Execute;
    friend GBCpuState_InterruptCheck;
private:
    static GBInstruction s_InstructionTable[INSTRUCTIONS_NUM];
    static GBInstruction s_CBInstructionTable[INSTRUCTIONS_NUM];

    quint64 m_Cycles;
    quint16 m_PC;
    quint16 m_SP;
    union
    {
        long long All;
        quint8 Single[REG8_NUM];
        quint16_be Double[REG16_NUM];
    } m_Registers;
    bool m_IME;
    IGBCpuState* m_State;

    void SetState(IGBCpuState* newState);
    void SetFlag(Flag flagMask, bool value);
    bool GetFlag(Flag flagMask) { return (m_Registers.Single[*CpuRegister::F] & *flagMask) != 0; }

    //instructions
    bool LD_r_n(GBInstructionContext* context, GBBus* bus);
    bool LD_r1_r2(GBInstructionContext* context, GBBus* bus);
    bool LD_addr_A(GBInstructionContext* context, GBBus* bus);
    bool LD_A_addr(GBInstructionContext* context, GBBus* bus);
    bool LD_off_A(GBInstructionContext* context, GBBus* bus);
    bool LD_rr_nn(GBInstructionContext* context, GBBus* bus);
    bool PUSH(GBInstructionContext* context, GBBus* bus);
    bool POP(GBInstructionContext* context, GBBus* bus);
    bool XOR(GBInstructionContext* context, GBBus* bus);
    bool CP(GBInstructionContext* context, GBBus* bus);
    bool INC_r(GBInstructionContext* context, GBBus* bus);
    bool INC_rr(GBInstructionContext* context, GBBus* bus);
    bool DEC_r(GBInstructionContext* context, GBBus* bus);
    bool LDD(GBInstructionContext* context, GBBus* bus);
    bool LDI(GBInstructionContext* context, GBBus* bus);
    bool CALL(GBInstructionContext* context, GBBus* bus);
    bool RET(GBInstructionContext* context, GBBus* bus);
    bool BIT(GBInstructionContext* context, GBBus* bus);
    bool JR(GBInstructionContext* context, GBBus* bus);
    bool RL(GBInstructionContext* context, GBBus* bus);
    bool RLA(GBInstructionContext* context, GBBus* bus);
public:
    GBCpu();
    ~GBCpu() override;
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBCPU_H
