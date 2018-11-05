#ifndef GBLENGTHCOUNTER_H
#define GBLENGTHCOUNTER_H

#include <QtGlobal>
#include "GBAudioCommonDefs.h"

class GBLengthCounter
{
private:
    const quint8 c_LengthMask;

    bool m_IsEnabled;
    quint8* m_Registers;

    bool PerformCheck() { return (m_Registers[AUDIO_CHANNEL_NR4_IDX] & 0x40) != 0; }
    bool DecreaseLength();
public:
    GBLengthCounter(quint8 lengthMask, quint8* registers);
    void Reset();
    void Tick();
    bool IsEnabled() { return m_IsEnabled; }
};

#endif // GBLENGTHCOUNTER_H
