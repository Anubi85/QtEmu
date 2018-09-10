#include "GBHardware.h"

GBHardware::GBHardware() :
    m_Registers(MMIO_SIZE, 0)
{
    Reset();
}

void GBHardware::Reset()
{
    GBComponent::Reset();
    m_Registers[IO::SOUND_NR52] = static_cast<char>(0xF0);
    m_Registers[IO::BIOS_MAPPING] = static_cast<char>(0x00);
}

quint8 GBHardware::ReadIO(quint16 address)
{
    quint16 idx = address - ADDRESS_OFFSET;
    switch (idx)
    {
    case IO::SOUND_NR52:
    case IO::BIOS_MAPPING:
        return static_cast<quint8>(m_Registers[idx]);
    default:
        m_ErrorCode = 1; //TODO use proper error code
#ifdef DEBUG
        qDebug("Write on IO register 0x%04X", address);
#endif
        return 0;
    }
}

void GBHardware::WriteIO(quint16 address, quint8 value)
{
    quint16 idx = address - ADDRESS_OFFSET;
    switch (idx)
    {
    case IO::SOUND_NR52:
        m_Registers[IO::SOUND_NR52] = static_cast<char>(value & 0x80);
        break;
    case IO::BIOS_MAPPING:
        m_Registers[IO::BIOS_MAPPING] = static_cast<char>(value & 0x01);
        break;
    default:
        m_ErrorCode = 2;
#ifdef DEBUG
        qDebug("Read from IO register 0x%04X", address);
#endif
        break;
    }
}
