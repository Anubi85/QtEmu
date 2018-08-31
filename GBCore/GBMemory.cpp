#include "GBMemory.h"
#include <QCryptographicHash>

GBMemory::GBMemory()
{
    Reset();
}

void GBMemory::Reset()
{
    m_Bios.clear();
    m_IsBiosMapped = true;
}

bool GBMemory::LoadBios(QString biosFilePath)
{
    if (QFile::exists(biosFilePath))
    {
        QFile biosFile(biosFilePath);
        if (biosFile.open(QFile::ReadOnly))
        {
            QByteArray tmp = biosFile.readAll();
            if (tmp.length() == BIOS_SIZE && QCryptographicHash::hash(tmp, QCryptographicHash::Md5).toHex() == BIOS_MD5)
            {
                m_Bios = tmp;
            }
            biosFile.close();
        }
    }
    return !m_Bios.isEmpty();
}

quint8 GBMemory::ReadByte(quint16 address)
{
    if (address < 0x100 && m_IsBiosMapped)
    {
        return static_cast<quint8>(m_Bios[address]);
    }
    return 0;
}

quint16 GBMemory::ReadWord(quint16 address)
{
    return static_cast<quint16>(ReadByte(address) | ReadByte(address + 1) << 8);
}

void GBMemory::WriteByte(quint16 address, quint8 value)
{
    //check for special address
    if (address == BIOS_MAPPED_ADDRESS)
    {
        //disable bios mapping if set to 1
        m_IsBiosMapped = value != 1;
    }
}

void GBMemory::WriteWord(quint16 address, quint16 value)
{
    WriteByte(address, value & 0x00FF);
    WriteByte(address + 1, (value & 0xFF00) >> 8);
}
