#include "IGBVolumeManager.h"

IGBVolumeManager::IGBVolumeManager(quint8* registers)
{
    m_Registers = registers;
    Reset();
}

IGBVolumeManager::~IGBVolumeManager() {}

void IGBVolumeManager::Reset()
{
    m_Sample = 0;
}
