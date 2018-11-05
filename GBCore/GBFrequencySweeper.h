#ifndef GBFREQUENCYSWEEPER_H
#define GBFREQUENCYSWEEPER_H

#include <QtGlobal>
#include "GBAudioCommonDefs.h"

class GBFrequencySweeper
{
private:
    bool m_IsEnabled;
    quint8 m_PeriodCounter;
    quint8* m_Registers;

    quint8 GetShift(quint8 NRx0) { return NRx0 & 0x07; }
    bool ShallIncrease(quint8 NRx0) { return (NRx0 & 0x08) == 0; }
    quint8 GetPeriod(quint8 NRx0) { return (NRx0 & 0x70) >> 4; }
public:
    GBFrequencySweeper(quint8* registers);
    void Reset();
    void Tick();
    bool IsEnabled() { return m_IsEnabled; }
};

#endif // GBFREQUENCYSWEEPER_H
