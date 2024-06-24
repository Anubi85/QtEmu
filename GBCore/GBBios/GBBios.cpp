#include <QString>
#include <QFile>
#include <QCryptographicHash>
#include "GBBios.h"
#include "GBBus.h"

void GBBios::Reset()
{
    GBComponent::Reset();
    memset(m_Data, 0, BIOS_SIZE);
    m_IsBiosLoaded = false;
    m_IsBiosMapped = true;
}

bool GBBios::Load(QString biosFilePath)
{
    if (QFile::exists(biosFilePath))
    {
        QFile biosFile(biosFilePath);
        if (biosFile.open(QFile::ReadOnly))
        {
            QByteArray tmp = biosFile.readAll();
            if (tmp.length() == BIOS_SIZE)
            {
                if (QCryptographicHash::hash(tmp, QCryptographicHash::Md5).toHex() == BIOS_MD5)
                {
                    memcpy(m_Data, tmp.data(), BIOS_SIZE);
                    m_IsBiosLoaded = true;
                }
                else
                {
                    m_ErrorCode = Error::BIOS_WrongFileMD5;
                }
            }
            else
            {
                m_ErrorCode = Error::BIOS_WrongFileSize;
            }
            biosFile.close();
        }
        else
        {
            m_ErrorCode = Error::BIOS_FailToOpen;
        }
    }
    else
    {
        m_ErrorCode = Error::BIOS_FileNotFound;
    }
    return m_IsBiosLoaded;
}

void GBBios::Tick(GBBus* bus)
{
    //Check if BIOS data has been properly loaded
    if (m_IsBiosMapped && m_IsBiosLoaded)
    {
        //Check if BIOS data has been requested
		if (bus->MainBus()->IsReadReqPending() && (bus->MainBus()->GetAddress() <= BIOS_SIZE))
        {
			bus->MainBus()->ReadReqAck();
			bus->MainBus()->SetData(static_cast<quint8>(m_Data[bus->MainBus()->GetAddress()]));
        }
    }
    //Check for BIOS unmap command
	if (bus->MainBus()->IsWriteReqPending() && (bus->MainBus()->GetAddress() == BIOS_UNMAP_REGISTER))
    {
		m_IsBiosMapped = (bus->MainBus()->GetData() & 0x01) == 0;
		bus->MainBus()->WriteReqAck();
    }
}
