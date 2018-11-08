#ifndef GBAUDIOMODULE_DIVIDERVOLUMEMANAGER_H
#define GBAUDIOMODULE_DIVIDERVOLUMEMANAGER_H

#include <QtGlobal>
#include "IGBAudioModule.h"
#include "GBAudioCommonDefs.h"

#define VOLUME_FACTORS_NUM 4

class GBAudioModule_DividerVolumeManager : public IGBAudioModule
{
private:
    static quint8 s_VolumeFactors[VOLUME_FACTORS_NUM];

    quint8 GetVolume() { return (m_Registers[AUDIO_CHANNEL_NR2_IDX] &0x60) >> 5; }
public:
    GBAudioModule_DividerVolumeManager(quint8* registers);
    void Tick() override;
};

#endif // GBAUDIOMODULE_DIVIDERVOLUMEMANAGER_H
