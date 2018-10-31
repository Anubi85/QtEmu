#ifndef GBFREQUENCYSWEEPER_H
#define GBFREQUENCYSWEEPER_H

#include <QtGlobal>

class GBFrequencySweeper
{
private:
    quint8 m_PeriodCounter;

    quint8 GetShift(quint8 NRx0) { return NRx0 & 0x07; }
    bool ShallIncrease(quint8 NRx0) { return (NRx0 & 0x08) == 0; }
    quint8 GetPeriod(quint8 NRx0) { return (NRx0 & 0x70) >> 4; }
public:
    GBFrequencySweeper();
    void Reset();
    bool Tick(quint8 NRx0, quint16* frequency);
};

#endif // GBFREQUENCYSWEEPER_H
