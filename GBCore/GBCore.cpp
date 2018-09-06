#include "GBCore.h"
#include "GBMemory.h"

IEmulatorCore* GetCore()
{
    return new GBCore();
};

GBCore::GBCore()
{
    m_Memory = new GBMemory();
    m_Cpu = new GBCpu(m_Memory);
}

GBCore::~GBCore()
{
    delete m_Memory;
}

bool GBCore::LoadBios(QString biosFilePath)
{
    if (m_Memory != nullptr)
    {
        return m_Memory->LoadBios(biosFilePath);
    }
    return false;
}

void GBCore::Exec()
{
    if (m_Cpu != nullptr)
    {
        m_Cpu->Exec();
    }
}

bool GBCore::HasError()
{
    return m_Cpu->HasError() || m_Memory->HasError();
}
