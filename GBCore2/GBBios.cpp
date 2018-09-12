#include "GBBios.h"
#include "GBBus.h"

GBBios::GBBios() :
    m_Data(BIOS_SIZE, 0)
{
    Reset();
}

void GBBios::Reset()
{
    GBComponent::Reset();
    m_Data.fill(0);
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
            if (tmp.length() == BIOS_SIZE && QCryptographicHash::hash(tmp, QCryptographicHash::Md5).toHex() == BIOS_MD5)
            {
                m_Data = tmp;
            }
            biosFile.close();
        }
    }
    m_IsBiosLoaded = m_Data.count('\0')!= BIOS_SIZE;
    return m_IsBiosLoaded;
}

void GBBios::Tick(GBBus* bus)
{
    //Check if BIOS data has been properly loaded
    if (m_IsBiosMapped & m_IsBiosLoaded)
    {
        //Check if BIOS data has been requested
        if (bus->IsReadReqPending() && (bus->GetAddress() <= BIOS_SIZE))
        {
            bus->ReadReqAck();
            bus->SetData(static_cast<quint8>(m_Data[bus->GetAddress()]));
        }
    }
    //Check for BIOS unmap command
    if (bus->IsWriteReqPending() && (bus->GetAddress() == BIOS_UNMAP))
    {
        m_IsBiosMapped = (bus->GetData() & 0x01) == 0;
    }
}
