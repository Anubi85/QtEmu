#include "QtGBMemory.h"
#include <QFile>

QtGBMemory::QtGBMemory()
{
    m_IsBiosLoaded = false;
}

bool QtGBMemory::LoadBios(QString biosFilePath)
{
	QFile biosFile(biosFilePath);
    bool result = biosFile.open(QFile::ReadOnly);
    if (result)
    {
        QByteArray bios = biosFile.readAll();
        m_IsBiosLoaded = bios.count() == BIOS_SIZE;
        if (m_IsBiosLoaded)
        {
            m_Bios = bios;
        }
        biosFile.close();
    }
    return result;
}

quint8 QtGBMemory::ReadByte(quint16 address)
{
    if (address < 0x0100 && m_IsBiosLoaded)
    {
        return static_cast<quint8>(m_Bios[address]);
    }
    else
    {
        return 0;
    }
}

quint16 QtGBMemory::ReadWord(quint16 address)
{
    return static_cast<quint16>(ReadByte(address) << 8 | ReadByte(address + 1));
}

void QtGBMemory::WriteByte(quint16 address, quint8 value)
{

}

void QtGBMemory::WriteWord(quint16 address, quint16 value)
{
	WriteByte(address, value & 0x00FF);
	WriteByte(address + 1, (value & 0xFF00) >> 8);
}
