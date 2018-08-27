#include "IQtGBMemory.h"
#include "QtGBMemory.h"

IQtGBMemory::~IQtGBMemory() {}

IQtGBMemory* IQtGBMemory::GetInstance()
{
    static QtGBMemory instance;
    return &instance;
}
