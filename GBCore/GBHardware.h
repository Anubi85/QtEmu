#ifndef GBHARDWARE_H
#define GBHARDWARE_H

#include <QtCore>
#include "GBComponent.h"

//Memory Mapped IO size
#define MMIO_SIZE 0x00E0
//Address offset for acessing data
#define ADDRESS_OFFSET 0xFEA0

namespace IO
{
    enum
    {
        SOUND_NR10 = 0xFF10,
        SOUND_NR11 = 0xFF11,
        SOUND_NR12 = 0xFF12,
        SOUND_NR13 = 0xFF13,
        SOUND_NR14 = 0xFF14,
        SOUND_NR21 = 0xFF16,
        SOUND_NR22 = 0xFF17,
        SOUND_NR23 = 0xFF18,
        SOUND_NR24 = 0xFF19,
        SOUND_NR30 = 0xFF1A,
        SOUND_NR31 = 0xFF1B,
        SOUND_NR32 = 0xFF1C,
        SOUND_NR33 = 0xFF1D,
        SOUND_NR34 = 0xFF1E,
        SOUND_NR41 = 0xFF20,
        SOUND_NR42 = 0xFF21,
        SOUND_NR43 = 0xFF22,
        SOUND_NR44 = 0xFF23,
        SOUND_NR50 = 0xFF24,
        SOUND_NR51 = 0xFF25,
        SOUND_NR52 = 0xFF26,
        LCD_CONTROL = 0xFF40,
        SCROLL_Y = 0xFF42,
        LCD_Y = 0xFF44,
        BACKGROUND_PALETTE = 0xFF47,
        BIOS_MAPPING = 0xFF50,
    };
};

class GBHardware : public GBComponent
{
private:
    QByteArray m_Registers;
    quint8 ReadAudioReg(quint16 address);
    void WriteAudioReg(quint16 address, quint8 value);
    quint8 ReadVideoReg(quint16 address);
    void WriteVideoReg(quint16 address, quint8 value);
public:
    GBHardware();
    void Reset() override;
    bool IsBiosMapped() { return (m_Registers[IO::BIOS_MAPPING] & 0x01) == 0; }
    bool IsAudioEnabled() { return (m_Registers[IO::SOUND_NR52] & 0xF0) != 0; }
    quint8 ReadIO(quint16 address);
    void WriteIO(quint16 address, quint8 value);
};

#endif // GBHARDWARE_H
