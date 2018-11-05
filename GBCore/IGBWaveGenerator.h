#ifndef IGBWAVEGENERATOR_H
#define IGBWAVEGENERATOR_H

#include <QtGlobal>

class IGBWaveGenerator
{
protected:
    quint8 m_Sample;
    quint16 m_Counter;
    bool m_Enabled;
    quint8* m_Registers;

    IGBWaveGenerator(quint8* registers);
public:
    virtual ~IGBWaveGenerator();
    virtual void Reset();
    virtual void Tick() = 0;
    quint8 GetSample() { return m_Sample; }
    bool IsEnabled() { return m_Enabled; }
};

#endif // IGBWAVEGENERATOR_H
