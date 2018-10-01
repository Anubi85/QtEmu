#include "GBCore.h"
#include "GBBus.h"
#include "GBCpu.h"
#include "GBBios.h"
#include "GBVideo.h"
#include "GBAudio.h"
#include "GBCartridge.h"
#include "GBInternalRam.h"

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
        case Component::Video:
            m_Components[comp] = new GBVideo();
            break;
        case Component::Audio:
            m_Components[comp] = new GBAudio();
            break;
        case Component::InternalRAM:
            m_Components[comp] = new GBInternalRam();
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
    GBBios* bios = new GBBios();
    if (bios->Load(biosFilePath))
    {
        delete m_Components[*Component::BIOS];
        m_Components[*Component::BIOS] = bios;
        return true;
    }
    return false;
}

bool GBCore::LoadRom(QString romFilePath)
{
    GBCartridge* cartridge = new GBCartridge();
    if (cartridge->Load(romFilePath))
    {
        delete m_Components[*Component::Cartridge];
        m_Components[*Component::Cartridge] = cartridge;
        return true;
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
        if (m_Components[comp] != nullptr)
        {
            hasError |= m_Components[comp]->HasError();
        }
    }
    return hasError;
}
