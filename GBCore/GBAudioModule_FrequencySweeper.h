#ifndef GBAUDIOMODULE_FREQUENCYSWEEPER_H
#define GBAUDIOMODULE_FREQUENCYSWEEPER_H

#include <QtGlobal>
#include "GBAudioCommonDefs.h"
#include "IGBAudioModule.h"

class GBAudioModule_FrequencySweeper : public IGBAudioModule
{
private:
    quint8 m_PeriodCounter;

    quint8 GetShift(quint8 NRx0) { return NRx0 & 0x07; }
    bool ShallIncrease(quint8 NRx0) { return (NRx0 & 0x08) == 0; }
    quint8 GetPeriod(quint8 NRx0) { return (NRx0 & 0x70) >> 4; }
public:
    GBAudioModule_FrequencySweeper(quint8* registers);
    void Reset() override;
    void Tick() override;
};

#endif // GBAUDIOMODULE_FREQUENCYSWEEPER_H
