#include "QtGBCPU.h"

QtGBCPU::QtGBCPU()
{
    m_Memory = IQtGBMemory::GetInstance();
    //clear the registers
    Reset();
    //initialize instructions array
	for (int i = 0; i < Instructions::Total; i++)
	{
		m_Instructions[i] = nullptr;
	}
	m_Instructions[Instructions::NOP] = std::bind(&QtGBCPU::NOP, this, std::placeholders::_1);
	m_Instructions[Instructions::LD_8Bit] = std::bind(&QtGBCPU::LD_8Bit, this, std::placeholders::_1);
	m_Instructions[Instructions::LD_16Bit] = std::bind(&QtGBCPU::LD_16Bit, this, std::placeholders::_1);
    m_Instructions[Instructions::LDD] = std::bind(&QtGBCPU::LDD, this, std::placeholders::_1);
	m_Instructions[Instructions::XOR] = std::bind(&QtGBCPU::XOR, this, std::placeholders::_1);
	m_Instructions[Instructions::CP] = std::bind(&QtGBCPU::CP, this, std::placeholders::_1);
}

void QtGBCPU::Reset()
{
    m_ErrorOccurred = false;
    m_Registers.All = 0;
    m_PC = 0;
    m_SP = 0;
	m_Cycles = 0;
}

Instruction QtGBCPU::Decode(quint8 opCode)
{
	switch (GetX(opCode))
	{
		case 0:
            return Decode0(opCode);
		case 1:
            return Decode1(opCode);
		case 2:
            return Decode2(opCode);
		case 3:
            return Decode3(opCode);
	}
	return nullptr;
}

Instruction QtGBCPU::Decode0(quint8 opCode)
{
    if (opCode == 0)
    {
        return m_Instructions[Instructions::NOP];
    }
    switch (GetZ(opCode))
    {
        case 0:
            break;
        case 1:
            if (GetF(opCode))
            {

            }
            else
            {
                return m_Instructions[Instructions::LD_16Bit];
            }
            break;
        case 2:
            switch (GetW(opCode))
            {
                case 0:
                case 1:
                case 2:
                    break;
                case 3:
                    return m_Instructions[Instructions::LDD];
            }
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            break;
    }
    return nullptr;
}

Instruction QtGBCPU::Decode1(quint8 opCode)
{
    if (opCode != 0x76)
    {
        return m_Instructions[Instructions::LD_8Bit];
    }
    return nullptr;
}

Instruction QtGBCPU::Decode2(quint8 opCode)
{
    switch (GetY(opCode))
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            return m_Instructions[Instructions::XOR];
        case 6:
        case 7:
            break;
    }
    return nullptr;
}

Instruction QtGBCPU::Decode3(quint8 opCode)
{
    switch (GetY(opCode))
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            return m_Instructions[Instructions::XOR];
        case 6:
        case 7:
            break;
    }
    return nullptr;
}

void QtGBCPU::Exec()
{
	quint8 opCode = m_Memory->ReadByte(m_PC++);
    //execure instruction
	Instruction inst = Decode(opCode);
    if (inst != nullptr)
    {
		inst(opCode);
#ifdef DEBUG
		qDebug("Op code 0x%x executed", opCode);
#endif
    }
    else
    {
        m_ErrorOccurred = true;
#ifdef DEBUG
		qDebug("Op code 0x%x not implemented", opCode);
#endif
    }
}

quint8 QtGBCPU::Add4Bit(quint8 value1, quint8 value2, quint8 *carry)
{
	quint8 result = value1 + value2 + *carry;
	*carry = (result & 0x1F) ? 1 : 0;
	return result;
}

quint8 QtGBCPU::AuxSUB(Byte value)
{
	//get register A value
	Byte regA = m_Registers.Single[Registers::A];
	quint8 carry = 1;
	//perform subtraction (add A and 2-complement of value 4 bit at time)
	quint8 result = Add4Bit(regA.LowNibble, ~value.LowNibble, &carry);
	m_Registers.Flags.H = carry == 1;
	result |= Add4Bit(regA.HighNibble, ~value.HighNibble, &carry) << 4;
	m_Registers.Flags.C = carry == 1;
	//set remaining flags
	m_Registers.Flags.Z = result == 0;
	m_Registers.Flags.N = true;
	//return the result
	return result;
}

void QtGBCPU::NOP(quint8 opCode)
{
    m_Cycles++;
}

void QtGBCPU::LD_8Bit(quint8 opCode)
{
	quint8 regAidx = GetY(opCode);
	quint8 regBidx = GetZ(opCode);
	quint8 value = 0;
	m_Cycles++;
	if (regBidx == Registers::ADDR_HL)
	{
		value = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
		m_PC++;
		m_Cycles++;
	}
	else
	{
		value = m_Registers.Single[regBidx].Value;
	}
	if (regAidx == Registers::ADDR_HL)
	{
		m_Memory->WriteByte(m_Registers.Double[Registers::HL], value);
	}
	else
	{
		m_Registers.Single[regAidx].Value = value;
	}
}

void QtGBCPU::LD_16Bit(quint8 opCode)
{
	//get value from memory
	quint16 value = m_Memory->ReadWord(m_PC);
	m_PC += 2;
	m_Cycles += 3;
	//write value on register
	quint8 regIdx = GetW(opCode);
	if (regIdx == Registers::SP)
	{
		m_SP = value;
	}
	else
	{
		m_Registers.Double[regIdx] = value;
	}
}

void QtGBCPU::LDD(quint8 opCode)
{
    if (GetF(opCode))
    {
        m_Registers.Single[Registers::A].Value = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
    }
    else
    {
        m_Memory->WriteByte(m_Registers.Double[Registers::HL], m_Registers.Single[Registers::A].Value);
    }
    m_Registers.Double[Registers::HL]--;
    m_Cycles += 2;
}

void QtGBCPU::CP(quint8 opCode)
{
	//check if value must be read from memory
	Byte value;
	quint8 regIdx = GetZ(opCode);
	if (opCode & MASK_BIT7)
	{
		value.Value = m_Memory->ReadByte(m_PC++);
	}
	else if (regIdx == Registers::ADDR_HL)
	{
		value.Value = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
	}
	else
	{
		value = m_Registers.Single[regIdx];
	}
	//set flags
	AuxSUB(value);
}

void QtGBCPU::XOR(quint8 opCode)
{
	Byte value;
	quint8 regIdx = GetZ(opCode);
	m_Cycles++;
	if (opCode & MASK_BIT7)
	{
		value.Value = m_Memory->ReadByte(m_PC++);
		m_Cycles++;
	}
	else if (regIdx == Registers::ADDR_HL)
	{
		value.Value = m_Memory->ReadByte(m_Registers.Double[Registers::HL]);
		m_Cycles++;
	}
	else
	{
		value = m_Registers.Single[regIdx];
	}
	m_Registers.Single[Registers::A].Value ^= value.Value;
	//set flags
	m_Registers.Flags.Z = m_Registers.Single[Registers::A].Value == 0;
	m_Registers.Flags.N = false;
	m_Registers.Flags.C = false;
	m_Registers.Flags.H = false;
}
