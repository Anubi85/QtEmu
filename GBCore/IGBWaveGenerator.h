#ifndef IGBWAVEGENERATOR_H
#define IGBWAVEGENERATOR_H

#include <QtGlobal>

class IGBWaveGenerator
{
protected:
    quint8 m_Sample;
    quint16 m_Period;
    quint16 m_Counter;

    IGBWaveGenerator();
public:
    virtual ~IGBWaveGenerator();
    virtual void Reset();
    virtual void Start() { m_Counter = m_Period; }
    virtual void SetPeriod(quint16 frequency) = 0;
    virtual void Tick(bool performSweep) = 0;
    quint8 GetSample() { return m_Sample; }
};

#endif // IGBWAVEGENERATOR_H
