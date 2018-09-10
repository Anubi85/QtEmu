#ifndef GBMEMORY_H
#define GBMEMORY_H

#include <QtCore>
#include "GBComponent.h"
#include "GBHardware.h"

#define BIOS_MD5 "32fbbd84168d3482956eb3c5051637f5"

//BIOS size
#define BIOS_SIZE 0x0100
//Cartridge ROM bank 0 size
#define BNK0_SIZE 0x4000
//Video RAM size
#define VRAM_SIZE 0x2000
//Working RAM size
#define WRAM_SIZE 0x2000
//Sprites RAM size
#define SRAM_SIZE 0x00A0
//RAM page zero size
#define ZRAM_SIZE 0x0080

//BIOS start address
#define BIOS_START_ADDRESS 0x0000
//Cartridge ROM bank 0 start address
#define ROM0_START_ADDRESS 0x0000
//Cartridge ROM switchable bank address
#define SROM_START_ADDRESS 0x4000
//Video RAM start address
#define VRAM_START_ADDRESS 0x8000
//Cartridge RAM start address
#define CRAM_START_ADDRESS 0xA000
//Working RAM start address
#define WRAM_START_ADDRESS 0xC000
//Sprites RAM start address
#define SRAM_START_ADDRESS 0xFE00
//Memory Mapped IO start address
#define MMIO_START_ADDRESS 0xFEA0
//RAM page zero start address
#define ZRAM_START_ADDRESS 0xFF80

enum class MemoryAreas
{
    BIOS, //BIOS area
    ROM0, //Cartridge ROM bank 0 area
    SROM, //Cartridge ROM switchable bank area
    CRAM, //Cartridge RAM area
    VRAM, //Video RAM area
    WRAM, //Working RAM area
    SRAM, //Sprites RAM area
    MMIO, //Memory mapped IO area
    ZRAM  //RAM page zero area
};

class GBMemory : public GBComponent
{
private:
    GBHardware* m_Hardware;

    QByteArray m_Bios;
    QByteArray m_ROM0;
    QByteArray m_ZRAM;
    QByteArray m_VRAM;
    bool m_IsBiosLoaded;
    bool m_IsRomLoaded;

    MemoryAreas GetSection(quint16 address);
public:
    GBMemory(GBHardware* hardware);
    void Reset() override;
    bool LoadBios(QString biosFilePath);
    quint8 ReadByte(quint16 address);
    quint16 ReadWord(quint16 address);
    void WriteByte(quint16 address, quint8 value);
    void WriteWord(quint16 address, quint16 value);
};

#endif // GBMEMORY_H
