#include "GBCpu.h"

GBCpu::GBCpu(GBMemory* memory)
{
    m_Memory = memory;
    Reset();
}

void GBCpu::Reset()
{
    m_PC = 0;
    m_SP = 0;
    m_Cycles = 0;
    m_Registers.All = 0;
    if (m_Memory != nullptr)
    {
        m_Memory->Reset();
    }
}
