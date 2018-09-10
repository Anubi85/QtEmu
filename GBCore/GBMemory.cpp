#include "GBMemory.h"
#include <QCryptographicHash>

GBMemory::GBMemory(GBHardware* hardware) :
    m_Bios(BIOS_SIZE, 0),
    m_ROM0(BNK0_SIZE, 0),
    m_ZRAM(ZRAM_SIZE, 0),
    m_VRAM(VRAM_SIZE, 0)
{
    m_Hardware = hardware;
    Reset();
}

void GBMemory::Reset()
{
    GBComponent::Reset();
    m_Bios.fill(0);
    m_ROM0.fill(0);
    m_ZRAM.fill(0);
    m_VRAM.fill(0);
    m_IsBiosLoaded = false;
    m_IsRomLoaded = false;
    if (m_Hardware != nullptr)
    {
        m_Hardware->Reset();
    }
}

MemoryAreas GBMemory::GetSection(quint16 address)
{
    //check if cartridge ROM bank 0 area
    if (address < SROM_START_ADDRESS)
    {
        //Check if BIOS area
        if ((address < BIOS_SIZE) && m_Hardware->IsBiosMapped())
        {
            return MemoryAreas::BIOS;
        }
        return MemoryAreas::ROM0;
    }
    //Check if cartridge ROM area
    if (address < VRAM_START_ADDRESS)
    {
        return MemoryAreas::SROM;
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
    m_IsBiosLoaded = m_Bios.count('\0')!= BIOS_SIZE;
    return m_IsBiosLoaded;
}

quint8 GBMemory::ReadByte(quint16 address)
{
    switch (GetSection(address))
    {
    case MemoryAreas::BIOS:
        return static_cast<quint8>(m_Bios[address]);
    case MemoryAreas::ROM0:
        if (m_IsRomLoaded)
        {
            return  static_cast<quint8>(m_ROM0[address]);
        }
        else
        {
#ifdef DEBUG
        qDebug("No ROM loaded");
#endif
            return 0;
        }
    case MemoryAreas::VRAM:
        return static_cast<quint8>(m_VRAM[address - VRAM_START_ADDRESS]);
    case MemoryAreas::MMIO:
        return m_Hardware->ReadIO(address);
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
        m_Hardware->WriteIO(address, value);
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
