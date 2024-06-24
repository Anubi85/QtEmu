#include "GBCore.h"
#include "GBBus.h"
#include "GBCpu.h"
#include "GBBios.h"
#include "GBRam.h"
#include "GBGpu.h"
#include "GBApu.h"
#include "GBCartridge.h"
#include "GBInternalRam.h"
#include "GBInterrupt.h"
#include "GBSerial.h"
#include "GBUnusedIO.h"
#include "GBUtils.h"

IEmulatorCore* GetCore()
{
    return new GBCore();
};

GBCore::GBCore()
{
	m_Bus = new GBBus();
    for (int comp = 0; comp < static_cast<int>(Component::Total); comp++)
    {
        m_Components[comp] = nullptr;
    }
}

GBCore::~GBCore()
{
    for (int comp = 0; comp < static_cast<int>(Component::Total); comp++)
    {
        delete m_Components[comp];
    }
	delete m_Bus;
}

void GBCore::Exec()
{
	if (m_Bus->MainBus()->IsReadReqPending())
    {
		m_Error = Error::MAINBUS_ReadRequestNotServed;
#ifdef DEBUG
		qDebug("[MAIN] Read request to a not implemented address 0x%04X", m_Bus->MainBus()->GetAddress());
#endif
    }
	else if (m_Bus->MainBus()->IsWriteReqPending())
    {
		m_Error = Error::MAINBUS_WriteRequestNotServed;
#ifdef DEBUG
		qDebug("[MAIN] Write request to a not implemented address 0x%04X", m_Bus->MainBus()->GetAddress());
#endif
    }
	else if (m_Bus->DmaBus()->IsReadReqPending())
	{
		m_Error = Error::DMABUS_ReadRequestNotServed;
#ifdef DEBUG
		qDebug("[DMA] Read request to a not implemented address 0x%04X", m_Bus->DmaBus()->GetAddress());
#endif
	}
	else if (m_Bus->DmaBus()->IsWriteReqPending())
	{
		m_Error = Error::DMABUS_WriteRequestNotServed;
#ifdef DEBUG
		qDebug("[DMA] Write request to a not implemented address 0x%04X", m_Bus->DmaBus()->GetAddress());
#endif
	}
    else
    {
        for (int comp = 0; comp < static_cast<int>(Component::Total); comp++)
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
    for (int comp = 0; comp < static_cast<int>(Component::Total); comp++)
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
    static_cast<GBGpu*>(m_Components[*Component::GPU])->GetScreenSize(width, height);
}

quint32* GBCore::GetVideoFrame()
{
    return static_cast<GBGpu*>(m_Components[*Component::GPU])->GetFrame();
}

quint32 GBCore::GetAudioBufferSize()
{
    return static_cast<GBApu*>(m_Components[*Component::APU])->GetSamplesBufferSize();
}

quint8* GBCore::GetAudioSamples()
{
    return  static_cast<GBApu*>(m_Components[*Component::APU])->GetSamples();
}

bool GBCore::Initialize(QString biosFilePath, QString romFilePath)
{
	m_Bus->Clear();
    bool res = true;
    for (int comp = 0; comp < static_cast<int>(Component::Total); comp++)
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
        case Component::GPU:
            m_Components[comp] = new GBGpu();
            break;
        case Component::APU:
            m_Components[comp] = new GBApu();
            break;
        case Component::InternalRAM:
            m_Components[comp] = new GBInternalRam();
            break;
		case Component::Interrupt:
			m_Components[comp] = new GBInterrupt();
			break;
        case Component::Serial:
            m_Components[comp] = new GBSerial();
            break;
		case Component::UnusedIO:
			m_Components[comp] = new GBUnusedIO();
			break;
        default:
            //TODO: remove default
            m_Components[comp] = nullptr;
            break;
        }
    }
    //TODO: handle error code in case res is false
    m_Error = Error::Ok;
    return res;
}
