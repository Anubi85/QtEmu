#include "GBInternalBus.h"

void GBInternalBus::Clear()
{
	m_Address = 0x0000;
	m_Data = 0x00;
	m_WriteReq = false;
	m_ReadReq = false;
}
