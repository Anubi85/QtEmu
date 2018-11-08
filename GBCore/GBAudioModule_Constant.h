#ifndef GBAUDIOMODULE_CONSTANT_H
#define GBAUDIOMODULE_CONSTANT_H

#include <QtGlobal>
#include "IGBAudioModule.h"

class GBAudioModule_Constant : public IGBAudioModule
{
private:
    const quint8 c_SampleValue;
public:
    GBAudioModule_Constant(quint8 sampleValue);
    void Reset() override { m_Sample = c_SampleValue; }
    void Tick() override {}
};

#endif // GBAUDIOMODULE_CONSTANT_H
