#ifndef GBAUDIOMODULE_NOISEWAVEGENERATOR_H
#define GBAUDIOMODULE_NOISEWAVEGENERATOR_H

#include <QtGlobal>
#include "IGBAudioModule.h"

class GBAudioModule_NoiseWaveGenerator : public IGBAudioModule
{
public:
    GBAudioModule_NoiseWaveGenerator(quint8* registers);
    void Tick() override;
};

#endif // GBAUDIOMODULE_NOISEWAVEGENERATOR_H
