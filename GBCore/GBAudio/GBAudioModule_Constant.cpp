#include "GBAudioModule_Constant.h"

GBAudioModule_Constant::GBAudioModule_Constant(quint8 sampleValue) :
    IGBAudioModule(nullptr),
    c_SampleValue(sampleValue)
{

}

void GBAudioModule_Constant::Reset()
{
     m_Sample = c_SampleValue;
     m_Enabled = true;
}
