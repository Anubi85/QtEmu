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
    for (int comp = 0; comp < *Component::TOTAL; comp++)
    {
        switch (static_cast<Component>(comp))
        {
        case Component::BIOS:
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
    for (int comp = 0; comp < *Component::TOTAL; comp++)
    {
        delete m_Components[comp];
    }
    delete m_Bus;
}

bool GBCore::LoadBios(QString biosFilePath)
{
    if (m_Components[*Component::BIOS] != nullptr)
    {
        return static_cast<GBBios*>(m_Components[*Component::BIOS])->Load(biosFilePath);
    }
    return false;
}

void GBCore::Exec()
{
    for (int comp = 0; comp < *Component::TOTAL; comp++)
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
    for (int comp = 0; comp < *Component::TOTAL; comp++)
    {
        hasError |= m_Components[comp]->HasError();
    }
    return hasError;
}
