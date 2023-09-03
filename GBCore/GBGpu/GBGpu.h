#pragma once

#include <QSemaphore>
#include "GBComponent.h"
#include "GBUtils.h"
#include "IGBGpuState.h"
#include "IGBGpuStateContext.h"

#define VIDEO_REG_SIZE 0x000C
#define VIDEO_REG_ADDRESS_OFFSET 0xFF40
#define VIDEO_RAM_SIZE 0x2000
#define VIDEO_RAM_ADDRESS_OFFSET 0x8000
#define VIDEO_VALID_OAM_SIZE 0x00A0
#define VIDEO_OAM_SIZE 0x0100
#define VIDEO_OAM_ADDRESS_OFFSET 0xFE00
#define PALETTE_NUM 10
#define PALETTE_SIZE 4

enum class VideoRegister
{
    LCDC = 0xFF40 - VIDEO_REG_ADDRESS_OFFSET,
    STAT = 0xFF41 - VIDEO_REG_ADDRESS_OFFSET,
    SCY = 0xFF42 - VIDEO_REG_ADDRESS_OFFSET,
    SCX = 0xFF43 - VIDEO_REG_ADDRESS_OFFSET,
    LY = 0xFF44 - VIDEO_REG_ADDRESS_OFFSET,
	LYC = 0xFF45 - VIDEO_REG_ADDRESS_OFFSET,//TO IMPLEMENT
	DMA = 0xFF46 - VIDEO_REG_ADDRESS_OFFSET,//TO IMPLEMENT
    BGP = 0xFF47 - VIDEO_REG_ADDRESS_OFFSET,
	OBP0 = 0xFF48 - VIDEO_REG_ADDRESS_OFFSET,
	OBP1 = 0xFF49 - VIDEO_REG_ADDRESS_OFFSET,
	WY = 0xFF4A - VIDEO_REG_ADDRESS_OFFSET,//TO IMPLEMENT
	WX = 0xFF4B - VIDEO_REG_ADDRESS_OFFSET,//TO IMPLEMENT
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

    GBBus* m_InternalBus;
    IGBGpuState* m_GpuStates[GPU_STATES_NUM];
    IGBGpuState* m_State;
    quint8 m_Registers[VIDEO_REG_SIZE];
    quint8 m_VideoRAM[VIDEO_RAM_SIZE];
	quint8 m_VideoOAM[VIDEO_VALID_OAM_SIZE];
    quint32 m_Cycles;
    quint32 m_ScreenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
    QSemaphore m_FrameSemaphore;

    bool IsAddressInVideoRAM(quint16 address) { return address >= VIDEO_RAM_ADDRESS_OFFSET && address < VIDEO_RAM_ADDRESS_OFFSET + VIDEO_RAM_SIZE; }
    bool IsAddressInVideoReg(quint16 address) { return address >= VIDEO_REG_ADDRESS_OFFSET && address < VIDEO_REG_ADDRESS_OFFSET + VIDEO_REG_SIZE; }
	bool IsAddressInVideoOAM(quint16 address) { return address >= VIDEO_OAM_ADDRESS_OFFSET && address < VIDEO_OAM_ADDRESS_OFFSET + VIDEO_OAM_SIZE; }
    GpuState GetVideoMode() { return static_cast<GpuState>(m_Registers[*VideoRegister::STAT] & 0x03); }
    void SetVideoMode(GpuState newMode) { m_Registers[*VideoRegister::STAT] = (m_Registers[*VideoRegister::STAT] & 0xFC) | static_cast<quint8>(newMode); }
    void ReadVideoRAM(GBBus* bus, bool modeOverride);
    void WriteVideoRAM(GBBus* bus);
	void ReadVideoOAM(GBBus* bus, bool modeOverride);
	void WriteVideoOAM(GBBus* bus);
    void ReadVideoRegister(GBBus* bus);
    void WriteVideoRegister(GBBus* bus);
    //IGBVideoStateContext
	quint32 PerformCycle() override { return ++m_Cycles; }
    void SetState(GpuState newStateId) override;
	bool IsDisplayEnabled() override { return (m_Registers[*VideoRegister::LCDC] & 0x80) != 0; }
	void ResetCycles() override { m_Cycles = 0; }
	void IncreaseYLineCount() override { m_Registers[*VideoRegister::LY] = (m_Registers[*VideoRegister::LY] + 1) % VIDEO_MAX_Y_LINE_COUNT; }
	quint8 GetYLineCount() override { return m_Registers[*VideoRegister::LY]; }
    bool GetBackgroundTileMap() override { return (m_Registers[*VideoRegister::LCDC] & 0x08) != 0; }
    bool GetBackgroundTileID() override { return (m_Registers[*VideoRegister::LCDC] & 0x10) != 0; }
    quint8 GetYScroll() override { return m_Registers[*VideoRegister::SCY]; }
    quint8 GetXScroll() override { return m_Registers[*VideoRegister::SCX]; }
    void SetPixel(quint8 pixelIdx, quint8 pixelValue) override;
    void FrameReady() override { m_FrameSemaphore.release(); }
public:
    GBGpu();
    ~GBGpu() override;
    void Reset() override;
    void Tick(GBBus* bus, GBInterruptBus* interruptBus) override;
    void GetScreenSize(int& w, int& h) { w = SCREEN_WIDTH; h = SCREEN_HEIGHT; }
    quint32* GetFrame();
};
