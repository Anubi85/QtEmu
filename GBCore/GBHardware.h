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
