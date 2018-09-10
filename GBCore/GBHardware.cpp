#include "GBHardware.h"

GBHardware::GBHardware() :
    m_Registers(MMIO_SIZE, 0)
{
    Reset();
}

void GBHardware::Reset()
{
    GBComponent::Reset();
    m_Registers[IO::SOUND_NR10] = static_cast<char>(0x80);
    m_Registers[IO::SOUND_NR11] = static_cast<char>(0xBF);
    m_Registers[IO::SOUND_NR12] = static_cast<char>(0xF3);
    m_Registers[IO::SOUND_NR13] = static_cast<char>(0xF3);
    m_Registers[IO::SOUND_NR14] = static_cast<char>(0x3F);
    m_Registers[IO::SOUND_NR21] = static_cast<char>(0x3F);
    m_Registers[IO::SOUND_NR22] = static_cast<char>(0x00);
    m_Registers[IO::SOUND_NR23] = static_cast<char>(0xFF);
    m_Registers[IO::SOUND_NR24] = static_cast<char>(0x3F);
    m_Registers[IO::SOUND_NR30] = static_cast<char>(0x7F);
    m_Registers[IO::SOUND_NR31] = static_cast<char>(0xFF);
    m_Registers[IO::SOUND_NR32] = static_cast<char>(0x9F);
    m_Registers[IO::SOUND_NR33] = static_cast<char>(0xFF);
    m_Registers[IO::SOUND_NR34] = static_cast<char>(0x3F);
    m_Registers[IO::SOUND_NR41] = static_cast<char>(0xFF);
    m_Registers[IO::SOUND_NR42] = static_cast<char>(0x00);
    m_Registers[IO::SOUND_NR43] = static_cast<char>(0x00);
    m_Registers[IO::SOUND_NR44] = static_cast<char>(0x3F);
    m_Registers[IO::SOUND_NR50] = static_cast<char>(0x77);
    m_Registers[IO::SOUND_NR51] = static_cast<char>(0xF3);
    m_Registers[IO::SOUND_NR52] = static_cast<char>(0xF0);
    m_Registers[IO::BIOS_MAPPING] = static_cast<char>(0x00);
}

quint8 GBHardware::ReadIO(quint16 address)
{
    quint16 idx = address - ADDRESS_OFFSET;
    quint8 mask;
    switch (idx)
    {
    case IO::SOUND_NR10:
        mask = 0x80;
        break;
    case IO::SOUND_NR11:
    case IO::SOUND_NR21:
        mask = 0x3F;
        break;
    case IO::SOUND_NR13:
    case IO::SOUND_NR23:
    case IO::SOUND_NR41:
        mask = 0xFF;
        break;
    case IO::SOUND_NR14:
    case IO::SOUND_NR24:
    case IO::SOUND_NR34:
    case IO::SOUND_NR44:
        mask = 0xBF;
        break;
    case IO::SOUND_NR30:
        mask = 0x7F;
        break;
    case IO::SOUND_NR32:
        mask = 0x9F;
        break;
    case IO::SOUND_NR52:
        mask = 0x70;
        break;
    case IO::SOUND_NR12:
    case IO::SOUND_NR22:
    case IO::SOUND_NR31:
    case IO::SOUND_NR33:
    case IO::SOUND_NR42:
    case IO::SOUND_NR43:
    case IO::SOUND_NR50:
    case IO::SOUND_NR51:
    case IO::BIOS_MAPPING:
        mask = 0x00;
        break;
    default:
        m_ErrorCode = 1; //TODO use proper error code
#ifdef DEBUG
        qDebug("Write on IO register 0x%04X", address);
#endif
        return 0;
    }
    return static_cast<quint8>(m_Registers[idx] | mask);
}

void GBHardware::WriteIO(quint16 address, quint8 value)
{
    quint16 idx = address - ADDRESS_OFFSET;
    quint8 mask;
    switch (idx)
    {
    case IO::SOUND_NR10:
        mask = 0x7F;
        break;
    case IO::SOUND_NR14:
    case IO::SOUND_NR24:
    case IO::SOUND_NR34:
        mask = 0xCF;
        break;
    case IO::SOUND_NR30:
    case IO::SOUND_NR52:
        mask = 0x80;
        break;
    case IO::SOUND_NR32:
        mask = 0x60;
        break;
    case IO::SOUND_NR41:
        mask = 0x3F;
        break;
    case IO::SOUND_NR44:
        mask = 0xC0;
        break;
    case IO::BIOS_MAPPING:
        mask = 0x01;
        break;
    case IO::SOUND_NR11:
    case IO::SOUND_NR12:
    case IO::SOUND_NR13:
    case IO::SOUND_NR21:
    case IO::SOUND_NR22:
    case IO::SOUND_NR23:
    case IO::SOUND_NR31:
    case IO::SOUND_NR33:
    case IO::SOUND_NR42:
    case IO::SOUND_NR43:
    case IO::SOUND_NR50:
    case IO::SOUND_NR51:
        mask = 0xFF;
        break;
    default:
        m_ErrorCode = 2;
#ifdef DEBUG
        qDebug("Read from IO register 0x%04X", address);
#endif
        return;
    }
    m_Registers[idx] = static_cast<char>(value & mask);
}
