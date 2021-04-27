#include "GBCore.h"
#include "GBBus.h"
#include "GBCpu.h"
#include "GBBios.h"
#include "GBRam.h"
#include "GBGpu.h"
#include "GBAudio.h"
#include "GBCartridge.h"
#include "GBInternalRam.h"
#include "GBUtils.h"

IEmulatorCore* GetCore()
{
    return new GBCore();
};

GBCore::GBCore()
{
    m_Bus = new GBBus();
    for (int comp = 0; comp < COMPONENT_NUM; comp++)
    {
        m_Components[comp] = nullptr;
    }
}

GBCore::~GBCore()
{
    for (int comp = 0; comp < COMPONENT_NUM; comp++)
    {
        delete m_Components[comp];
    }
    delete m_Bus;
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
        for (int comp = 0; comp < COMPONENT_NUM; comp++)
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
    for (int comp = 0; comp < COMPONENT_NUM; comp++)
    {
        if (m_Components[comp] != nullptr)
        {
            hasError |= m_Components[comp]->HasError();
        }
    }
    return hasError;
}

void GBCore::GetScreenSize(int& width, int& height)
{
    static_cast<GBGpu*>(m_Components[*Component::Video])->GetScreenSize(width, height);
}

quint32* GBCore::GetFrame()
{
    return static_cast<GBGpu*>(m_Components[*Component::Video])->GetFrame();
}

bool GBCore::Initialize(QString biosFilePath, QString romFilePath)
{
    m_Bus->Clear();
    bool res = true;
    for (int comp = 0; comp < COMPONENT_NUM; comp++)
    {
        delete m_Components[comp];
        switch (static_cast<Component>(comp))
        {
        case Component::CPU:
            m_Components[comp] = new GBCpu();
            break;
        case Component::BIOS:
        {
            GBBios* bios = new GBBios();
            if (!biosFilePath.isEmpty())
            {
                if (bios->Load(biosFilePath))
                {
                    m_Components[comp] = bios;
                }
                else
                {
                    res = false;
                }
            }
            break;
        }
        case Component::RAM:
            m_Components[comp] = new GBRam();
            break;
        case Component::Cartridge:
        {
            GBCartridge* cartridge = new GBCartridge();
            if (!romFilePath.isEmpty())
            {
                if (cartridge->Load(romFilePath))
                {
                    m_Components[comp] = cartridge;
                    break;
                }
            }
            res = false;
            break;
        }
        case Component::Video:
            m_Components[comp] = new GBGpu();
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
    //TODO: handle error code in case res is false
    m_Error = Error::Ok;
    return res;
}
