#ifndef GBWAVEGENERATOR_SQUARE_H
#define GBWAVEGENERATOR_SQUARE_H

#include "IGBWaveGenerator.h"

#define DUTY_CYCLES_NUM 4
#define DUTY_CYCLES_SAMPLES_NUM 8

class GBWaveGenerator_Square : public IGBWaveGenerator
{
private:
    static quint8 s_DutyCycles[DUTY_CYCLES_NUM][DUTY_CYCLES_SAMPLES_NUM];

    quint8 m_SampleIdx;
    quint8 m_DutyIdx;
    quint8 m_SweepPeriod;
    quint8 m_SweepPeriodCounter;
    quint8 m_SweepShift;
    bool m_SweepDecrease;
public:
    GBWaveGenerator_Square();
    void Reset() override;
    void SetPeriod(quint16 frequency) override { m_Frequency = frequency; }
    void SetDutyCicle(quint8 dutyCycle) { m_DutyIdx = dutyCycle; }
    void SetSweep(quint8 value);
    void Tick(bool performSweep) override;
};

#endif // GBWAVEGENERATOR_SQUARE_H
