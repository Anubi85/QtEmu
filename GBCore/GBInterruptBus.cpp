#include "GBInterruptBus.h"

void GBInterruptBus::Clear()
{
    m_Interrupts = 0x00;
    m_InterruptsReq = 0x00;
    m_InterruptsAck = 0xFF;
}
