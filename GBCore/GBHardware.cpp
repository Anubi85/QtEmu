#include "GBHardware.h"

GBHardware::GBHardware() :
    m_Registers(MMIO_SIZE, 0)
{
    Reset();
}

quint8 GBHardware::ReadAudioReg(quint16 address)
{
    switch (address)
    {
    case IO::SOUND_NR10:
    case IO::SOUND_NR11:
    case IO::SOUND_NR12:
    case IO::SOUND_NR13:
    case IO::SOUND_NR14:
    case IO::SOUND_NR21:
    case IO::SOUND_NR22:
    case IO::SOUND_NR23:
    case IO::SOUND_NR24:
    case IO::SOUND_NR30:
    case IO::SOUND_NR31:
    case IO::SOUND_NR32:
    case IO::SOUND_NR33:
    case IO::SOUND_NR34:
    case IO::SOUND_NR41:
    case IO::SOUND_NR42:
    case IO::SOUND_NR43:
    case IO::SOUND_NR44:
    case IO::SOUND_NR50:
    case IO::SOUND_NR51:
    case IO::SOUND_NR52:
        return static_cast<quint8>(m_Registers[address - ADDRESS_OFFSET]);
    default:
        m_ErrorCode = 3; //TODO use proper error code
#ifdef DEBUG
        qDebug("Read audio from wrong register 0x%04X", address);
#endif
        return 0;
    }
}

void GBHardware::WriteAudioReg(quint16 address, quint8 value)
{
    switch (address)
    {
    case IO::SOUND_NR10:
    case IO::SOUND_NR11:
    case IO::SOUND_NR12:
    case IO::SOUND_NR13:
    case IO::SOUND_NR14:
    case IO::SOUND_NR21:
    case IO::SOUND_NR22:
    case IO::SOUND_NR23:
    case IO::SOUND_NR24:
    case IO::SOUND_NR30:
    case IO::SOUND_NR31:
    case IO::SOUND_NR32:
    case IO::SOUND_NR33:
    case IO::SOUND_NR34:
    case IO::SOUND_NR41:
    case IO::SOUND_NR42:
    case IO::SOUND_NR43:
    case IO::SOUND_NR44:
    case IO::SOUND_NR50:
    case IO::SOUND_NR51:
    case IO::SOUND_NR52:
        m_Registers[address - ADDRESS_OFFSET] = static_cast<char>(value);
        break;
    default:
        m_ErrorCode = 4; //TODO use proper error code
#ifdef DEBUG
        qDebug("Write audio to wrong register 0x%04X", address);
#endif
        break;
    }
}

quint8 GBHardware::ReadVideoReg(quint16 address)
{
    switch (address)
    {
    case IO::LCD_CONTROL:
    case IO::LCD_Y:
    case IO::SCROLL_Y:
    case IO::BACKGROUND_PALETTE:
        return static_cast<quint8>(m_Registers[address - ADDRESS_OFFSET]);
    default:
        m_ErrorCode = 5; //TODO use proper error code
#ifdef DEBUG
        qDebug("Read video from wrong register 0x%04X", address);
#endif
        return 0;
    }
}

void GBHardware::WriteVideoReg(quint16 address, quint8 value)
{
    switch (address)
    {
    case IO::LCD_CONTROL:
    case IO::LCD_Y:
    case IO::SCROLL_Y:
    case IO::BACKGROUND_PALETTE:
        m_Registers[address - ADDRESS_OFFSET] = static_cast<char>(value);
        break;
    default:
        m_ErrorCode = 6; //TODO use proper error code
#ifdef DEBUG
        qDebug("Write video to wrong register 0x%04X", address);
#endif
        break;
    }
}

void GBHardware::Reset()
{
    GBComponent::Reset();
    WriteIO(IO::SOUND_NR10, 0x80);
    WriteIO(IO::SOUND_NR11, 0xBF);
    WriteIO(IO::SOUND_NR12, 0xF3);
    WriteIO(IO::SOUND_NR13, 0xF3);
    WriteIO(IO::SOUND_NR14, 0x3F);
    WriteIO(IO::SOUND_NR21, 0x3F);
    WriteIO(IO::SOUND_NR22, 0x00);
    WriteIO(IO::SOUND_NR23, 0xFF);
    WriteIO(IO::SOUND_NR24, 0x3F);
    WriteIO(IO::SOUND_NR30, 0x7F);
    WriteIO(IO::SOUND_NR31, 0xFF);
    WriteIO(IO::SOUND_NR32, 0x9F);
    WriteIO(IO::SOUND_NR33, 0xFF);
    WriteIO(IO::SOUND_NR34, 0x3F);
    WriteIO(IO::SOUND_NR41, 0xFF);
    WriteIO(IO::SOUND_NR42, 0x00);
    WriteIO(IO::SOUND_NR43, 0x00);
    WriteIO(IO::SOUND_NR44, 0x3F);
    WriteIO(IO::SOUND_NR50, 0x77);
    WriteIO(IO::SOUND_NR51, 0xF3);
    WriteIO(IO::SOUND_NR52, 0xF0);
    WriteIO(IO::LCD_CONTROL, 0x91);
    WriteIO(IO::SCROLL_Y, 0x00);
    WriteIO(IO::LCD_Y, 0x00);
    WriteIO(IO::BACKGROUND_PALETTE, 0xFC);
    WriteIO(IO::BIOS_MAPPING, 0x00);
}

quint8 GBHardware::ReadIO(quint16 address)
{
    quint8 mask;
    switch (address)
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
    case IO::LCD_CONTROL:
    case IO::SCROLL_Y:
    case IO::LCD_Y:
    case IO::BACKGROUND_PALETTE:
    case IO::BIOS_MAPPING:
        mask = 0x00;
        break;
    default:
        m_ErrorCode = 1; //TODO use proper error code
#ifdef DEBUG
        qDebug("Read from IO register 0x%04X", address);
#endif
        return 0;
    }
    return static_cast<quint8>(m_Registers[address - ADDRESS_OFFSET] | mask);
}

void GBHardware::WriteIO(quint16 address, quint8 value)
{
    quint8 mask;
    switch (address)
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
    case IO::LCD_CONTROL:
    case IO::SCROLL_Y:
    case IO::BACKGROUND_PALETTE:
        mask = 0xFF;
        break;
    case IO::LCD_Y:
        mask = 0x00;
        break;
    default:
        m_ErrorCode = 2;
#ifdef DEBUG
        qDebug("Write to IO register 0x%04X", address);
#endif
        return;
    }
    m_Registers[address - ADDRESS_OFFSET] = static_cast<char>(value & mask);
}
