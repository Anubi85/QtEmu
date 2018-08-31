#include "GBCore.h"
#include "GBMemory.h"

IEmulatorCore* GetCore()
{
    return new GB();
};

GB::GB()
{
    m_Memory = new GBMemory();
    m_Cpu = new GBCpu(m_Memory);
}

GB::~GB()
{
    delete m_Memory;
}

bool GB::LoadBios(QString biosFilePath)
{
    if (m_Memory)
    {
        return m_Memory->LoadBios(biosFilePath);
    }
    return false;
}

void GB::Exec()
{
}
