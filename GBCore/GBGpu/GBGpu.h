#pragma once

#include <QSemaphore>
#include "GBComponent.h"
#include "GBUtils.h"
#include "IGBGpuState.h"
#include "IGBGpuStateContext.h"
#include "GBMemoryMap.h"

class IGBBus;
class GBDma;
class GBInterruptBus;

#define PALETTE_NUM 10
#define PALETTE_SIZE 4
#define STAT_VIDEO_MODE_MASK 0x03
#define STAT_LINE_COUNT_MASK 0x04
#define STAT_HBLANK_INTERRUPT_MASK 0x08
#define STAT_VBLANK_INTERRUPT_MASK 0x10
#define STAT_SCANLINE1_INTERRUPT_MASK 0x20
#define STAT_LINE_COUNT_INTERRUPT_MASK 0x40

enum class VideoRegister
{
	LCDC = 0xFF40 - GPU_REGISTERS_ADDRESS,
	STAT = 0xFF41 - GPU_REGISTERS_ADDRESS,
	SCY = 0xFF42 - GPU_REGISTERS_ADDRESS,
	SCX = 0xFF43 - GPU_REGISTERS_ADDRESS,
	LY = 0xFF44 - GPU_REGISTERS_ADDRESS,
	LYC = 0xFF45 - GPU_REGISTERS_ADDRESS,
	DMA = 0xFF46 - GPU_REGISTERS_ADDRESS,
	BGP = 0xFF47 - GPU_REGISTERS_ADDRESS,
	OBP0 = 0xFF48 - GPU_REGISTERS_ADDRESS,
	OBP1 = 0xFF49 - GPU_REGISTERS_ADDRESS,
	WY = 0xFF4A - GPU_REGISTERS_ADDRESS,
	WX = 0xFF4B - GPU_REGISTERS_ADDRESS,
};

enum class Palette
{
    Monochrome,
    MonochromeInverted,
    RedLight,
    RedDark,
    YellowLight,
    YellowDark,
    GreenLight,
    GreenDark,
    BlueLight,
    BlueDark,
};

class GBGpu : IGBGpuStateContext, public GBComponent
{
private:
    static quint32 s_Palettes[PALETTE_NUM][PALETTE_SIZE];

    IGBGpuState* m_GpuStates[GPU_STATES_NUM];
    IGBGpuState* m_State;
	GBDma* m_Dma;
	quint8 m_Registers[GPU_REGISTERS_SIZE];
	quint8 m_VideoRAM[GPU_RAM_SIZE];
	quint8 m_VideoOAM[OAM_VALID_SIZE];
    quint32 m_Cycles;
    quint32 m_ScreenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
    QSemaphore m_FrameSemaphore;
	bool m_IsWindowActive;
	quint8 m_WindowLineCount;

	bool IsAddressInVideoRAM(quint16 address) { return address >= GPU_RAM_ADDRESS && address < GPU_RAM_ADDRESS + GPU_RAM_SIZE; }
	bool IsAddressInVideoReg(quint16 address) { return address >= GPU_REGISTERS_ADDRESS && address < GPU_REGISTERS_ADDRESS + GPU_REGISTERS_SIZE; }
	bool IsAddressInVideoOAM(quint16 address) { return address >= OAM_ADDRESS && address < OAM_ADDRESS + OAM_TOTAL_SIZE; }
	GpuState GetVideoMode() { return static_cast<GpuState>(m_Registers[*VideoRegister::STAT] & STAT_VIDEO_MODE_MASK); }
	void SetVideoMode(GpuState newMode, GBInterruptBus* interruptBus);
	void CheckYLine(GBInterruptBus* interruptBus);
	void ReadVideoRAM(IGBBus* bus, bool modeOverride);
	void WriteVideoRAM(IGBBus* bus);
	void ReadVideoOAM(IGBBus* bus, bool modeOverride);
	void WriteVideoOAM(IGBBus* bus);
	void ReadVideoRegister(IGBBus* bus);
	void WriteVideoRegister(IGBBus* bus);
    //IGBVideoStateContext
	quint32 PerformCycle() override { return ++m_Cycles; }
    void SetState(GpuState newStateId) override;
	bool IsDisplayEnabled() override { return (m_Registers[*VideoRegister::LCDC] & 0x80) != 0; }
	bool IsBackgroundEnabled() override { return (m_Registers[*VideoRegister::LCDC] & 0x01) != 0; }
	bool IsWindowEnabled() override { return (m_Registers[*VideoRegister::LCDC] & 0x21) == 0x21; }
	void ResetCycles() override { m_Cycles = 0; }
	void IncreaseYLineCount() override { m_Registers[*VideoRegister::LY] = (m_Registers[*VideoRegister::LY] + 1) % VIDEO_MAX_Y_LINE_COUNT; }
	void IncreaseWindowLineCount() override { m_WindowLineCount++; }
	void ResetWindowLineCount() override { m_WindowLineCount = 0; }
	quint8 GetYLineCount() override { return m_Registers[*VideoRegister::LY]; }
	quint8 GetWindowLineCount() override { return  m_WindowLineCount; }
	quint8 GetWindowYCoord() override { return m_Registers[*VideoRegister::WY]; }
	quint8 GetWindowXCoord() override { return m_Registers[*VideoRegister::WX] - 7; }
	bool IsWindowActive() override { return m_IsWindowActive; }
	void ActivateWindow(bool active) override { m_IsWindowActive = active; }
    bool GetBackgroundTileMap() override { return (m_Registers[*VideoRegister::LCDC] & 0x08) != 0; }
	bool GetWindowTileMap() override { return (m_Registers[*VideoRegister::LCDC] & 0x40) != 0; }
	bool GetTileID() override { return (m_Registers[*VideoRegister::LCDC] & 0x10) != 0; }
    quint8 GetYScroll() override { return m_Registers[*VideoRegister::SCY]; }
    quint8 GetXScroll() override { return m_Registers[*VideoRegister::SCX]; }
    void SetPixel(quint8 pixelIdx, quint8 pixelValue) override;
    void FrameReady() override { m_FrameSemaphore.release(); }
public:
    GBGpu();
    ~GBGpu() override;
    void Reset() override;
	void Tick(GBBus* bus) override;
    void GetScreenSize(int& w, int& h) { w = SCREEN_WIDTH; h = SCREEN_HEIGHT; }
    quint32* GetFrame();
};
