#include "GBBus.h"

void GBBus::Clear()
{
	m_Address = 0x0000;
	m_Data = 0x00;
    m_WriteReq = false;
    m_ReadReq = false;
	m_Interrupts = 0x00;
	m_InterruptsReq = 0x00;
	m_InterruptsAck = 0xFF;
}
