#pragma once

/**************
 * MEMORY MAP *
**************/
//BIOS
#define BIOS_ADDRESS				0x0000
#define BIOS_SIZE					0x0100
//Cartridge ROM
#define CARTRIDGE_ROM_ADDRESS		0x0000
#define CARTRIDGE_ROM_SIZE			0x8000
//Gpu RAM
#define GPU_RAM_ADDRESS				0x8000
#define GPU_RAM_SIZE				0x2000
//Cartridge RAM
#define CARTRIDGE_RAM_ADDRESS		0xA000
#define CARTRIDGE_RAM_SIZE			0x2000
//RAM
#define RAM_ADDRESS					0xC000
#define RAM_SIZE					0x2000
#define RAM_ECHO_SIZE				0x1E00
//OAM (Object Attribute Memory)
#define OAM_ADDRESS					0xFE00
#define OAM_VALID_SIZE				0x00A0
#define OAM_TOTAL_SIZE				0x0100
//I/O Registers
#define IO_REGISTERS_ADDRESS		0xFF00
#define IO_REGISTERS_SIZE			0x004C
#define IO_UNUSED_REGISTERS_ADDRESS	0xFF4C
#define IO_UNUSED_REGISTERS_SIZE	0x0034
#define APU_REGISTERS_ADDRESS		0xFF10
#define APU_REGISTERS_SIZE			0x0030
#define APU_RAM_ADDRESS				0xFF30
#define APU_RAM_SIZE				0x0010
#define GPU_REGISTERS_ADDRESS		0xFF40
#define GPU_REGISTERS_SIZE			0x000C
//Internal RAM
#define HRAM_ADDRESS				0xFF80
#define HRAM_SIZE					0x007F

/*********************
 * I/O REGISTERS MAP *
*********************/
//Controller
#define P1_REGISTER					0xFF00
//Serial comunication
#define SB_REGISTER					0xFF01
#define SC_REGISTER					0xFF02
//Timer
#define DIV_REGISTER				0xFF04
#define TIMA_REGISTER				0xFF05
#define TMA_REGISTER				0xFF06
#define TAC_REGISTER				0xFF07
//APU
#define NR10_REGISTER				0xFF10
#define NR11_REGISTER				0xFF11
#define NR12_REGISTER				0xFF12
#define NR13_REGISTER				0xFF13
#define NR14_REGISTER				0xFF14
#define NR20_REGISTER				0xFF15
#define NR21_REGISTER				0xFF16
#define NR22_REGISTER				0xFF17
#define NR23_REGISTER				0xFF18
#define NR24_REGISTER				0xFF19
#define NR30_REGISTER				0xFF1A
#define NR31_REGISTER				0xFF1B
#define NR32_REGISTER				0xFF1C
#define NR33_REGISTER				0xFF1D
#define NR34_REGISTER				0xFF1E
#define NR40_REGISTER				0xFF1F
#define NR41_REGISTER				0xFF20
#define NR42_REGISTER				0xFF21
#define NR43_REGISTER				0xFF22
#define NR44_REGISTER				0xFF23
#define NR50_REGISTER				0xFF24
#define NR51_REGISTER				0xFF25
#define NR52_REGISTER				0xFF26
//GPU
#define LCDC_REGISTER				0xFF40
#define STAT_REGISTER				0xFF41
#define SCY_REGISTER				0xFF42
#define SCX_REGISTER				0xFF43
#define LY_REGISTER					0xFF44
#define LYC_REGISTER				0xFF45
#define DMA_REGISTER				0xFF46
#define BGP_REGISTER				0xFF47
#define OBP0_REGISTER				0xFF48
#define OBP1_REGISTER				0xFF49
#define WY_REGISTER					0xFF4A
#define WX_REGISTER					0xFF4B
//BIOS
#define BIOS_UNMAP_REGISTER			0xFF50
//Interrupts
#define IF_REGISTER					0xFF0F
#define IE_REGISTER					0xFFFF
