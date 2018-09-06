#include "GBMemory.h"
#include <QCryptographicHash>

GBMemory::GBMemory() :
    m_Bios(BIOS_SIZE, 0),
    m_ZRAM(ZRAM_SIZE, 0),
    m_VRAM(VRAM_SIZE, 0)
{
    Reset();
}

void GBMemory::Reset()
{
    m_ErrorCode = 0;
    m_Bios.fill(0);
    m_ZRAM.fill(0);
    m_VRAM.fill(0);
    m_IsBiosMapped = true;
}

MemoryAreas GBMemory::GetSection(quint16 address)
{
    //Check if cartridge ROM area
    if (address < VRAM_START_ADDRESS)
    {
        //Check if BIOS area
        if ((address < BIOS_SIZE) && m_IsBiosMapped)
        {
            return MemoryAreas::BIOS;
        }
        return MemoryAreas::CROM;
    }
    //Check if video RAM area
    else if (address < CRAM_START_ADDRESS)
    {
        return MemoryAreas::VRAM;
    }
    //Check if working RAM area
    else if (address < WRAM_START_ADDRESS)
    {
        return MemoryAreas::WRAM;
    }
    //Check if cartridge RAM area
    else if (address < SRAM_START_ADDRESS)
    {
        return MemoryAreas::CRAM;
    }
    //Check if in sprites RAM area
    else if (address < MMIO_START_ADDRESS)
    {
        return MemoryAreas::SRAM;
    }
    //Check if in memory mapped IO area
    else if (address < ZRAM_START_ADDRESS)
    {
        return MemoryAreas::MMIO;
    }
    //Page zero RAM area
    else
    {
        return MemoryAreas::ZRAM;
    }
}

void GBMemory::MMIOWrite(quint16 address, quint8 value)
{
    if (address == BIOS_MAPPED_ADDRESS)
    {
        //disable bios mapping if set to 1
        m_IsBiosMapped = value != 1;
        return;
    }
}

quint8 GBMemory::MMIORead(quint16 address)
{
    return 0;
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
    return m_Bios.count('\0')!= BIOS_SIZE;
}

quint8 GBMemory::ReadByte(quint16 address)
{
    switch (GetSection(address))
    {
    case MemoryAreas::BIOS:
        return static_cast<quint8>(m_Bios[address]);
    case MemoryAreas::VRAM:
        return static_cast<quint8>(m_VRAM[address - VRAM_START_ADDRESS]);
    case MemoryAreas::MMIO:
        return MMIORead(address);
    case MemoryAreas::ZRAM:
        return static_cast<quint8>(m_ZRAM[address - ZRAM_START_ADDRESS]);
    default:
        m_ErrorCode = 1; //TODO put proper error code
#ifdef DEBUG
        qDebug("Read from address 0x%04X not implemented", address);
#endif
        return 0;
    }
}

quint16 GBMemory::ReadWord(quint16 address)
{
    return static_cast<quint16>(ReadByte(address) | ReadByte(address + 1) << 8);
}

void GBMemory::WriteByte(quint16 address, quint8 value)
{
    switch (GetSection(address))
    {
    case MemoryAreas::VRAM:
        m_VRAM[address - VRAM_START_ADDRESS] = static_cast<char>(value);
        break;
    case MemoryAreas::MMIO:
        MMIOWrite(address, value);
        break;
    case MemoryAreas::ZRAM:
        m_ZRAM[address - ZRAM_START_ADDRESS] = static_cast<char>(value);
        break;
    default:
        m_ErrorCode = 2; //TODO put proper error code
#ifdef DEBUG
        qDebug("Write to address 0x%04X not implemented", address);
#endif
        break;
    }
}

void GBMemory::WriteWord(quint16 address, quint16 value)
{
    WriteByte(address, value & 0x00FF);
    WriteByte(address + 1, (value & 0xFF00) >> 8);
}
