#ifndef QTGBCPU_H
#define QTGBCPU_H

#include "IQtGBCPU.h"
#include "IQtGBMemory.h"
#include <functional>

#define REG_8BIT_NUM	8
#define REG_16BIT_NUM	4

#define MASK_BIT1		0x01
#define MASK_BIT2		0x02
#define MASK_BIT3		0x04
#define MASK_BIT4		0x08
#define MASK_BIT5		0x10
#define MASK_BIT6		0x20
#define MASK_BIT7		0x40
#define MASK_BIT8		0x80

#define GetX(code) (code & 0xC0) >> 6
#define GetY(code) (code & 0x38) >> 3
#define GetZ(code) (code & 0x07)
#define GetW(code) (code & 0x30) >> 4
#define GetF(code) (code & 0x08) >> 3

enum Registers
{
	B =			0x0,
	C =			0x1,
	D =			0x2,
	E =			0x3,
	H =			0x4,
	L =			0x5,
	ADDR_HL =	0x6,
	A =			0x7,
	BC =		0x0,
	DE =		0x1,
	HL =		0x2,
	SP =		0x3,
};

enum Instructions
{
	NOP,
	LD_8Bit,
	LD_16Bit,
	XOR,
	CP,
	Total
};

union Byte
{
	quint8 Value;
	quint8 HighNibble : 4;
	quint8 LowNibble : 4;
};

typedef std::function<void(quint8)> Instruction;

class QtGBCPU : public IQtGBCPU
{
private:
    union
    {
        long long All;
		Byte Single[REG_8BIT_NUM];
		quint16 Double[REG_16BIT_NUM];
        struct
        {
			bool :52;
            bool C:1;
            bool H:1;
            bool N:1;
            bool Z:1;
        } Flags;
    } m_Registers;
	quint16 m_PC;
	quint16 m_SP;
	quint64 m_Cycles;
    IQtGBMemory* m_Memory;
	Instruction m_Instructions[Instructions::Total];
    bool m_ErrorOccurred;

	Instruction Decode(quint8 opCode);
	void NOP(quint8 opCode) {}
	void LD_8Bit(quint8 opCode);
	void LD_16Bit(quint8 opCode);
	void CP(quint8 opCode);
	void XOR(quint8 opCode);

	quint8 Add4Bit(quint8 value1, quint8 value2, quint8 *carry);
	quint8 AuxSUB(Byte value);
public:
    QtGBCPU();
    void Reset() override;
    void Exec() override;
    bool HasError() override { return m_ErrorOccurred; }
};

#endif // QTGBCPU_H
