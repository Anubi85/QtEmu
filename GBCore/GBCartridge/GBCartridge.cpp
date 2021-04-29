#include <QFile>
#include "GBCartridge.h"
#include "IGBCartridgeBehaviour.h"
#include "GBCartridgeBehaviour_RomOnly.h"

void GBCartridge::Reset()
{
    delete m_Behaviour;
    m_Behaviour = nullptr;
}

void GBCartridge::Tick(GBBus* bus)
{
    if (m_Behaviour != nullptr)
    {
        m_Behaviour->ProcessRequests(bus);
    }
}

bool GBCartridge::Load(QString romFilePath)
{
    Reset();
    if (QFile::exists(romFilePath))
    {
        QFile romFile(romFilePath);
        if (romFile.open(QFile::ReadOnly))
        {
            QByteArray tmp = romFile.readAll();
            //check cartridge type
            switch (static_cast<CartridgeType>(tmp.at(CARTRIDGE_TYPE_ADDRESS)))
            {
            case CartridgeType::ROM_ONLY:
                m_Behaviour = new GBCartridgeBehaviour_RomOnly(reinterpret_cast<quint8*>(tmp.data()));
                break;
            }
            romFile.close();
        }
        else
        {
            m_ErrorCode = Error::ROM_FailToOpen;
        }
    }
    else
    {
        m_ErrorCode = Error::ROM_FileNotFound;
    }
    return m_Behaviour != nullptr;
}
