#include "IGBWaveGenerator.h"

IGBWaveGenerator::IGBWaveGenerator(quint8* registers)
{
    m_Registers = registers;
    Reset();
}

IGBWaveGenerator::~IGBWaveGenerator() { }

void IGBWaveGenerator::Reset()
{
    m_Sample = 0;
    m_Counter = 0;
    m_Enabled = true;
}
