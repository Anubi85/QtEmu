#include "GBBus.h"

GBBus::GBBus()
{
    Clear();
}

void GBBus::Clear()
{
    m_Address = 0;
    m_Data = 0;
    m_WriteReq = false;
    m_ReadReq = false;
}
