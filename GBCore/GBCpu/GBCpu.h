#pragma once

#include <QtGlobal>
#include <QtEndian>
#include "GBComponent.h"
#include "GBInstruction.h"
#include "GBInstructionContext.h"
#include "GBUtils.h"
#include "IGBCpuState.h"
#include "IGBCpuStateContext.h"

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

enum class IMERequest
{
	None,
	Activate,
	Deactivate,
};

class GBCpu : IGBCpuStateContext, public GBComponent
{
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
	IMERequest m_IMERequest;
    bool m_IME;
    bool m_CB;
    quint8 m_OpCode;
    bool m_IsHandlingInterrupt;
    quint16 m_InterruptRoutineAddress;
    IGBCpuState* m_CpuStates[CPU_STATES_NUM];
    IGBCpuState* m_State;

    void SetFlag(Flag flagMask, bool value);
    bool GetFlag(Flag flagMask) { return (m_Registers.Single[*CpuRegister::F] & *flagMask) != 0; }
    quint8 GetHighNibble(quint8 val) { return (val & 0xF0) >> 4; }
    quint8 GetLowNibble(quint8 val) { return val & 0x0F; }
    quint8 ByteFromNibbles(quint8 high, quint8 low) { return static_cast<quint8>(high << 4) | (low & 0x0F); }
    bool HasCarry(quint8 nibble) { return (nibble & 0x10) != 0; }
    quint8 AddSub(quint8 value1, quint8 value2, bool isSub);
    //IGBCpuStateContext
    void SetState(CpuState newStateID) override;
    bool GetCBFlag() override { return m_CB; }
    void SetCBFlag(bool isCB) override { m_CB = isCB; }
	bool GetImeFlag() override { return m_IME; }
	quint16 GetPcAndIncrement() override { return m_PC++; }
    quint8 GetOpCode() override { return m_OpCode; }
    void SetOpCode(quint8 opCode) override { m_OpCode = opCode; }
	bool ExecuteOpCode(GBInstructionContext* ctx, IGBBus* bus) override;
    void ResetInterruptMode() override;
    void SetInterruptMode(quint16 interruptRoutineAddress) override;
    bool IsHandlingInterrupt() override { return m_IsHandlingInterrupt; }

    //instructions
	bool NOP(GBInstructionContext* context, IGBBus* bus);
	bool LD_r_n(GBInstructionContext* context, IGBBus* bus);
	bool LD_r1_r2(GBInstructionContext* context, IGBBus* bus);
	bool LD_addr_A(GBInstructionContext* context, IGBBus* bus);
	bool LD_A_addr(GBInstructionContext* context, IGBBus* bus);
	bool LD_off_A(GBInstructionContext* context, IGBBus* bus);
	bool LD_A_off(GBInstructionContext* context, IGBBus* bus);
	bool LD_rr_nn(GBInstructionContext* context, IGBBus* bus);
	bool PUSH(GBInstructionContext* context, IGBBus* bus);
	bool POP(GBInstructionContext* context, IGBBus* bus);
	bool XOR(GBInstructionContext* context, IGBBus* bus);
	bool OR(GBInstructionContext* context, IGBBus* bus);
	bool ADD(GBInstructionContext* context, IGBBus* bus);
	bool SUB(GBInstructionContext* context, IGBBus* bus);
	bool CP(GBInstructionContext* context, IGBBus* bus);
	bool INC_r(GBInstructionContext* context, IGBBus* bus);
	bool INC_rr(GBInstructionContext* context, IGBBus* bus);
	bool DEC_r(GBInstructionContext* context, IGBBus* bus);
	bool DEC_rr(GBInstructionContext* context, IGBBus* bus);
	bool LDD(GBInstructionContext* context, IGBBus* bus);
	bool LDI(GBInstructionContext* context, IGBBus* bus);
	bool CALL(GBInstructionContext* context, IGBBus* bus);
	bool RET(GBInstructionContext* context, IGBBus* bus);
	bool BIT(GBInstructionContext* context, IGBBus* bus);
	bool JP(GBInstructionContext* context, IGBBus* bus);
	bool JR(GBInstructionContext* context, IGBBus* bus);
	bool RL(GBInstructionContext* context, IGBBus* bus);
	bool RLA(GBInstructionContext* context, IGBBus* bus);
	bool EDI(GBInstructionContext* context, IGBBus* bus);
public:
    GBCpu();
    ~GBCpu() override;
    void Reset() override;
	void Tick(GBBus* bus) override;
};
