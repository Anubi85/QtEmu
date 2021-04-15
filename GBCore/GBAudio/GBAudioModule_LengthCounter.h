#ifndef GBAUDIOMODULE_LENGTHCOUNTER_H
#define GBAUDIOMODULE_LENGTHCOUNTER_H

#include <QtGlobal>
#include "GBAudioCommonDefs.h"
#include "IGBAudioModule.h"

class GBAudioModule_LengthCounter : public IGBAudioModule
{
private:
    const quint8 c_LengthMask;

    quint8 GetLenght() { return m_Registers[AUDIO_CHANNEL_NR1_IDX] & c_LengthMask; }
    void SetLength(quint8 value);
    bool PerformCheck() { return (m_Registers[AUDIO_CHANNEL_NR4_IDX] & 0x40) != 0; }
    void DecreaseLength();
public:
    GBAudioModule_LengthCounter(quint8 lengthMask, quint8* registers);
    void Reset() override;
    void Tick() override;
    void Trigger() override;
};

#endif // GBAUDIOMODULE_LENGTHCOUNTER_H
