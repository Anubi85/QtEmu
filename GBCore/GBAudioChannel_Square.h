#ifndef GBAUDIOCHANNEL_SQUARE_H
#define GBAUDIOCHANNEL_SQUARE_H

#include "GBAudioChannelBase.h"

#define DUTY_CICLES_NUM 4
#define DUTY_CICLES_VALUES_NUM 8

class GBAudioChannel_Square : public GBAudioChannelBase
{
private:
    static quint8 s_DutyCicleSamples[DUTY_CICLES_NUM][DUTY_CICLES_VALUES_NUM];

    quint8 m_DutyCicle;
    quint8 m_DutyStepCount;
    quint8 m_Volume;
    bool m_EnvelopeAddMode;
    quint8 m_Period;

    quint8 ReadNRx1() override { return static_cast<quint8>(m_DutyCicle << 6) | 0x3F; }
    quint8 ReadNRx2() override { return static_cast<quint8>(m_Volume << 4) | static_cast<quint8>( m_EnvelopeAddMode << 3) | static_cast<quint8>(m_Period & 0x07); }
    quint8 ReadNRx4() override { return static_cast<quint8>(m_LengthCounterEnabled << 6) | 0xBF; }
    void ProcessModules() override;
public:
    GBAudioChannel_Square();
    void Reset() override;
};

#endif // GBAUDIOCHANNEL_SQUARE_H
