#pragma once

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

class GBInterruptBus
{
private:
    quint8 m_InterruptsAck;
    quint8 m_Interrupts;
    quint8 m_InterruptsReq;
public:
    GBInterruptBus() { Clear(); }
    void Clear();
    void SetInterrupts(quint8 interrupts) { m_Interrupts = interrupts; }
    quint8 GetInterrupts() { return m_Interrupts; }
    void SetInterruptReq(Interrupt interrupt) { m_InterruptsReq |= (*interrupt); }
    quint8 GetInterruptsReq() { return m_InterruptsReq; }
    void SetInterruptAcq(Interrupt interrupt) { m_InterruptsAck &= ~(*interrupt); }
    quint8 GetInterruptsAck() { return m_InterruptsAck; }
};
