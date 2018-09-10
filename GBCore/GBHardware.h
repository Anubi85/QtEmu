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
        SOUND_NR10 = 0xFF10 - ADDRESS_OFFSET,
        SOUND_NR11 = 0xFF11 - ADDRESS_OFFSET,
        SOUND_NR12 = 0xFF12 - ADDRESS_OFFSET,
        SOUND_NR13 = 0xFF13 - ADDRESS_OFFSET,
        SOUND_NR14 = 0xFF14 - ADDRESS_OFFSET,
        SOUND_NR21 = 0xFF16 - ADDRESS_OFFSET,
        SOUND_NR22 = 0xFF17 - ADDRESS_OFFSET,
        SOUND_NR23 = 0xFF18 - ADDRESS_OFFSET,
        SOUND_NR24 = 0xFF19 - ADDRESS_OFFSET,
        SOUND_NR30 = 0xFF1A - ADDRESS_OFFSET,
        SOUND_NR31 = 0xFF1B - ADDRESS_OFFSET,
        SOUND_NR32 = 0xFF1C - ADDRESS_OFFSET,
        SOUND_NR33 = 0xFF1D - ADDRESS_OFFSET,
        SOUND_NR34 = 0xFF1E - ADDRESS_OFFSET,
        SOUND_NR41 = 0xFF20 - ADDRESS_OFFSET,
        SOUND_NR42 = 0xFF21 - ADDRESS_OFFSET,
        SOUND_NR43 = 0xFF22 - ADDRESS_OFFSET,
        SOUND_NR44 = 0xFF23 - ADDRESS_OFFSET,
        SOUND_NR50 = 0xFF24 - ADDRESS_OFFSET,
        SOUND_NR51 = 0xFF25 - ADDRESS_OFFSET,
        SOUND_NR52 = 0xFF26 - ADDRESS_OFFSET,
        BIOS_MAPPING = 0xFF50 - ADDRESS_OFFSET,
    };
};

class GBHardware : public GBComponent
{
private:
    QByteArray m_Registers;
public:
    GBHardware();
    void Reset() override;
    bool IsBiosMapped() { return (m_Registers[IO::BIOS_MAPPING] & 0x01) == 0; }
    bool IsAudioEnabled() { return (m_Registers[IO::SOUND_NR52] & 0xF0) != 0; }
    quint8 ReadIO(quint16 address);
    void WriteIO(quint16 address, quint8 value);
};

#endif // GBHARDWARE_H
