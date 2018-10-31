#include "GBFrequencySweeper.h"

GBFrequencySweeper::GBFrequencySweeper()
{
    Reset();
}

void GBFrequencySweeper::Reset()
{
    m_PeriodCounter = 0;
}

bool GBFrequencySweeper::Tick(quint8 NRx0, quint16* frequency)
{
    if ((GetShift(NRx0) != 0) && ((GetPeriod(NRx0) == 0) || (--m_PeriodCounter == 0)))
    {
        m_PeriodCounter = GetPeriod(NRx0);
        quint16 newFrequency = *frequency + static_cast<quint16>((ShallIncrease(NRx0) ? 1 : -1) * (*frequency >> GetPeriod(NRx0)));
        if (newFrequency >= 0x0800)
        {
            *frequency = 0x07FF;
            return false;
        }
        else
        {
            *frequency = newFrequency;
        }
    }
    return true;
}
