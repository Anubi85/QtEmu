#include "IGBWaveGenerator.h"

IGBWaveGenerator::IGBWaveGenerator()
{
    Reset();
}

IGBWaveGenerator::~IGBWaveGenerator() { }

void IGBWaveGenerator::Reset()
{
    m_Sample = 0;
    m_Period = 0;
    m_Counter = 0;
}
