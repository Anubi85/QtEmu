#include "IGBAudioModule.h"

IGBAudioModule::IGBAudioModule(quint8* registers)
{
    m_Registers = registers;
    Reset();
}

IGBAudioModule::~IGBAudioModule() {}

void IGBAudioModule::Reset()
{
    m_Sample = 0;
}
