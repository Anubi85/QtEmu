#pragma once

#include <QtGlobal>
#include "GBUtils.h"

enum class Interrupt
{
	None = 0x00,
	VBlank = 0x01,
	LcdStatus = 0x02,
	TimerOverflow = 0x04,
	SerialTransfer = 0x08,
	HiLo = 0x10,
};

class GBBus
{
private:
    quint16 m_Address;
    quint8 m_Data;
	bool m_WriteReq;
    bool m_ReadReq;
	quint8 m_InterruptsAck;
	quint8 m_Interrupts;
	quint8 m_InterruptsReq;
public:
    GBBus() { Clear(); }
    void Clear();
    void SetAddress(quint16 address) { m_Address = address; }
    quint16 GetAddress() { return m_Address; }
    quint16 GetLocalAddress(quint16 offset) { return m_Address - offset; }
    void SetData(quint8 data) { m_Data = data; }
    quint8 GetData() { return m_Data; }
	void SetInterrupts(quint8 interrupts) { m_Interrupts = interrupts; }
	quint8 GetInterrupts() { return m_Interrupts; }
	void SetInterruptReq(Interrupt interrupt) { m_InterruptsReq |= (*interrupt); }
	quint8 GetInterruptsReq() { return m_InterruptsReq; }
	void SetInterruptAcq(Interrupt interrupt) { m_InterruptsAck &= ~(*interrupt); }
	quint8 GetInterruptsAck() { return m_InterruptsAck; }
    void RequestWrite() { m_WriteReq = !m_ReadReq; } //allow write request only if no read request are pending
    void WriteReqAck() { m_WriteReq = false; }
    void RequestRead() { m_ReadReq = !m_WriteReq; } //allow read request only if no write request are pending
    void ReadReqAck() { m_ReadReq = false; }
    bool IsWriteReqPending() { return m_WriteReq; }
    bool IsReadReqPending() {return m_ReadReq; }
};
