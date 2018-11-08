#include "GBAudioModule_DividerVolumeManager.h"

GBAudioModule_DividerVolumeManager::GBAudioModule_DividerVolumeManager(quint8* registers) :
    IGBAudioModule(registers)
{

}

void GBAudioModule_DividerVolumeManager::Tick()
{
    m_Sample = s_VolumeFactors[GetVolume()];
}
