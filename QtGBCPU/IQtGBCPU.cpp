#include "IQtGBCPU.h"
#include "QtGBCPU.h"

IQtGBCPU::~IQtGBCPU() {}

IQtGBCPU* IQtGBCPU::GetInstance()
{
    static QtGBCPU instance;
    return &instance;
}
