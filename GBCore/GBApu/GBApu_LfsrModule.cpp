#include "GBApu_LfsrModule.h"

void GBApu_LfsrModule::Reset()
{
}

void GBApu_LfsrModule::Trigger()
{
    m_LFSR = 0x7FFF;
}

void GBApu_LfsrModule::Tick(bool doAction, quint8 *sample)
{
}
