#ifndef GBAUDIOMODULE_LENGTHCOUNTER_H
#define GBAUDIOMODULE_LENGTHCOUNTER_H

#include <QtGlobal>
#include "GBAudioCommonDefs.h"
#include "IGBAudioModule.h"

class GBAudioModule_LengthCounter : public IGBAudioModule
{
private:
    const quint8 c_LengthMask;

    bool PerformCheck() { return (m_Registers[AUDIO_CHANNEL_NR4_IDX] & 0x40) != 0; }
    bool DecreaseLength();
public:
    GBAudioModule_LengthCounter(quint8 lengthMask, quint8* registers);
    void Tick() override;
};

#endif // GBAUDIOMODULE_LENGTHCOUNTER_H
