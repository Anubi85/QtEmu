#ifndef IGBWAVEGENERATOR_H
#define IGBWAVEGENERATOR_H

#include <QtGlobal>

class IGBWaveGenerator
{
protected:
    quint8 m_Sample;
    quint16 m_Frequency;
    quint16 m_Counter;
    bool m_Enabled;

    IGBWaveGenerator();
public:
    virtual ~IGBWaveGenerator();
    virtual void Reset();
    virtual void Start() { m_Counter = m_Frequency; }
    virtual void SetPeriod(quint16 frequency) = 0;
    virtual void Tick(bool performSweep) = 0;
    quint8 GetSample() { return m_Sample; }
    bool IsEnabled() { return m_Enabled; }
};

#endif // IGBWAVEGENERATOR_H
