#include "GBWaveGenerator_Square.h"

void GBWaveGenerator_Square::Reset()
{
    IGBWaveGenerator::Reset();
    m_SampleIdx = 0;
    m_SweepShift = 0;
    m_SweepPeriod = 0;
    m_SweepPeriodCounter = 0;
    m_SweepDecrease = false;
}

void GBWaveGenerator_Square::SetSweep(quint8 value)
{
    m_SweepShift = value & 0x07;
    m_SweepDecrease = (value & 0x08) != 0;
    m_SweepPeriod = (value & 0x70) >> 4;
    m_SweepPeriodCounter = m_SweepPeriod;
}

void GBWaveGenerator_Square::Tick(bool performSweep)
{
    if (performSweep)
    {
        if ((m_SweepShift != 0) && ((m_SweepPeriod == 0) || (--m_SweepPeriodCounter == 0)))
        {
            m_SweepPeriodCounter = m_SweepPeriod;
            quint16 newFrequency = m_Frequency + static_cast<quint16>((m_SweepDecrease ? -1 : 1) * (m_Frequency >> m_SweepPeriod));
            if (newFrequency > 2047)
            {
                m_Enabled = false;
            }
            else
            {
                m_Frequency = newFrequency;
            }
        }
    }
    if ((m_Frequency == 0) || (--m_Counter == 0))
    {
        m_Counter = (2048 - m_Frequency) * 4;
        m_Sample = s_DutyCycles[m_DutyIdx][m_SampleIdx];
        ++m_SampleIdx &= 0x07;
    }
}
