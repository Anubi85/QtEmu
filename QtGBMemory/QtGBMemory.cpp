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

uchar QtGBMemory::ReadByte(ushort address)
{
    if (address < 0x0100 && m_IsBiosLoaded)
    {
		return static_cast<uchar>(m_Bios[address]);
    }
    else
    {
        return 0;
    }
}

ushort QtGBMemory::ReadWord(ushort address)
{
	return static_cast<ushort>(ReadByte(address) << 8 | ReadByte(address + 1));
}

void QtGBMemory::WriteByte(ushort address, uchar value)
{

}

void QtGBMemory::WriteWord(ushort address, ushort value)
{
	WriteByte(address, value & 0x00FF);
	WriteByte(address + 1, (value & 0xFF00) >> 8);
}
