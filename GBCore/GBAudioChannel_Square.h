#ifndef GBAUDIOCHANNEL_SQUARE_H
#define GBAUDIOCHANNEL_SQUARE_H

#include "GBAudioChannelBase.h"

#define DUTY_CICLES_NUM 4
#define DUTY_CICLES_VALUES_NUM 8

class GBAudioChannel_Square : public GBAudioChannelBase
{
protected:
    static quint8 s_DutyCicleSamples[DUTY_CICLES_NUM][DUTY_CICLES_VALUES_NUM];

    quint8 m_DutyCicle;
    quint8 m_DutyStepCount;
    quint8 m_Volume;
    quint8 m_CurrentVolume;
    bool m_EnvelopeAddMode;
    bool m_EnvelopCompleted;
    quint8 m_Period;
    quint8 m_PeriodCounter;

    GBAudioChannel_Square(quint16 addressOffset);
    quint8 ReadNRx1() override { return static_cast<quint8>(m_DutyCicle << 6) | 0x3F; }
    quint8 ReadNRx2() override { return static_cast<quint8>(m_Volume << 4) | static_cast<quint8>( m_EnvelopeAddMode << 3) | static_cast<quint8>(m_Period & 0x07); }
    quint8 ReadNRx4() override { return static_cast<quint8>(m_LengthCounterEnabled << 6) | 0xBF; }
    void WriteNRx1(quint8 value) override;
    void WriteNRx2(quint8 value) override;
    void WriteNRx3(quint8 value) override;
    void WriteNRx4(quint8 value) override;
    void ProcessModules() override;
public:
    GBAudioChannel_Square() : GBAudioChannel_Square(0xFF15) {}
    void Reset() override;
};

#endif // GBAUDIOCHANNEL_SQUARE_H
