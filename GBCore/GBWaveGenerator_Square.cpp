#include "GBWaveGenerator_Square.h"

void GBWaveGenerator_Square::Reset()
{
    IGBWaveGenerator::Reset();
    m_SampleIdx = 0;
}

void GBWaveGenerator_Square::Tick(bool performSweep)
{
    if (performSweep)
    {
        //perform frequency sweep
    }
    if ((m_Period == 0) || (--m_Counter == 0))
    {
        m_Counter = m_Period;
        m_Sample = s_DutyCycles[m_DutyIdx][m_SampleIdx];
        ++m_SampleIdx &= 0x07;
    }
}
