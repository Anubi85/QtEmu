#include "GBCore.h"
#include "GBBus.h"
#include "GBCpu.h"
#include "GBBios.h"
#include "GBLcdDisplay.h"

IEmulatorCore* GetCore()
{
    return new GBCore();
};

GBCore::GBCore()
{
    m_Bus = new GBBus();
    for (int comp = 0; comp < *Component::Total; comp++)
    {
        switch (static_cast<Component>(comp))
        {
        case Component::CPU:
            m_Components[comp] = new GBCpu();
            break;
        case Component::BIOS:
            m_Components[comp] = new GBBios();
            break;
        case Component::LCD_Display:
            m_Components[comp] = new GBLcdDisplay();
            break;
        default:
            m_Components[comp] = nullptr;
            break;
        }
    }
    m_Error = Error::Ok;
}

GBCore::~GBCore()
{
    for (int comp = 0; comp < *Component::Total; comp++)
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
    if (m_Bus->IsReadReqPending())
    {
        m_Error = Error::BUS_ReadRequestNotServed;
#ifdef DEBUG
        qDebug("Read request to a not implemented address 0x%04X", m_Bus->GetAddress());
#endif
    }
    else if (m_Bus->IsWriteReqPending())
    {
        m_Error = Error::BUS_WriteRequestNotServed;
#ifdef DEBUG
        qDebug("Write request to a not implemented address 0x%04X", m_Bus->GetAddress());
#endif
    }
    else
    {
        for (int comp = 0; comp < *Component::Total; comp++)
        {
            if (m_Components[comp] != nullptr)
            {
                m_Components[comp]->Tick(m_Bus);
            }
        }
    }
}

bool GBCore::HasError()
{
    bool hasError = m_Error != Error::Ok;
    for (int comp = 0; comp < *Component::Total; comp++)
    {
        hasError |= m_Components[comp]->HasError();
    }
    return hasError;
}
