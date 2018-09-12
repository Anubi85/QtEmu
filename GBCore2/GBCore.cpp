#include "GBCore.h"
#include "GBBus.h"
#include "GBBios.h"

IEmulatorCore* GetCore()
{
    return new GBCore();
};

GBCore::GBCore()
{
    m_Bus = new GBBus();
    for (int comp = 0; comp < GBComponents::ALL; comp++)
    {
        switch (comp)
        {
        case GBComponents::BIOS:
            m_Components[comp] = new GBBios();
            break;
        default:
            m_Components[comp] = nullptr;
            break;
        }
    }
}

GBCore::~GBCore()
{
    for (int comp = 0; comp < GBComponents::ALL; comp++)
    {
        delete m_Components[comp];
    }
    delete m_Bus;
}

bool GBCore::LoadBios(QString biosFilePath)
{
    if (m_Components[GBComponents::BIOS] != nullptr)
    {
        return static_cast<GBBios*>(m_Components[GBComponents::BIOS])->Load(biosFilePath);
    }
    return false;
}

void GBCore::Exec()
{
    for (int comp = 0; comp < GBComponents::ALL; comp++)
    {
        if (m_Components[comp] != nullptr)
        {
            m_Components[comp]->Tick(m_Bus);
        }
    }
}

bool GBCore::HasError()
{
    bool hasError = false;
    for (int comp = 0; comp < GBComponents::ALL; comp++)
    {
        hasError |= m_Components[comp]->HasError();
    }
    return hasError;
}
