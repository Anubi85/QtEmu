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
public:
    GBWaveGenerator_Square();
    void Reset() override;
    void SetPeriod(quint16 frequency) override { m_Period = (2048 - frequency) * 4; }
    void SetDutyCicle(quint8 dutyCycle) { m_DutyIdx = dutyCycle; }
    void Tick(bool performSweep) override;
};

#endif // GBWAVEGENERATOR_SQUARE_H
