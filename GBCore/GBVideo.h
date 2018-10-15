#ifndef GBLCDDISPLAY_H
#define GBLCDDISPLAY_H

#include <QSemaphore>
#include "GBComponent.h"
#include "GBUtils.h"
#include "IGBVideoStateContext.h"

#define VIDEO_REG_SIZE 0x000C
#define VIDEO_REG_ADDRESS_OFFSET 0xFF40
#define VIDEO_RAM_SIZE 0x2000
#define VIDEO_RAM_ADDRESS_OFFSET 0x8000

enum class VideoRegister
{
    LCDC = 0xFF40 - VIDEO_REG_ADDRESS_OFFSET,
    STAT = 0xFF41 - VIDEO_REG_ADDRESS_OFFSET,
    SCY = 0xFF42 - VIDEO_REG_ADDRESS_OFFSET,
    LY = 0xFF44 - VIDEO_REG_ADDRESS_OFFSET,
    BGP = 0xFF47 - VIDEO_REG_ADDRESS_OFFSET,
};

class IGBVideoState;
enum class VideoState;

class GBVideo : IGBVideoStateContext, public GBComponent
{
private:
    GBBus* m_InternalBus;
    IGBVideoState* m_State;
    quint8 m_Registers[VIDEO_REG_SIZE];
    quint8 m_VideoRAM[VIDEO_RAM_SIZE];
    quint32 m_Cycles;
    quint32 m_ScreenBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
    QSemaphore m_FrameSemaphore;

    bool IsAddressInVideoRAM(quint16 address) { return address >= VIDEO_RAM_ADDRESS_OFFSET && address < VIDEO_RAM_ADDRESS_OFFSET + VIDEO_RAM_SIZE; }
    bool IsAddressInVideoReg(quint16 address) { return address >= VIDEO_REG_ADDRESS_OFFSET && address < VIDEO_REG_ADDRESS_OFFSET + VIDEO_REG_SIZE; }
    VideoState GetVideoMode() { return static_cast<VideoState>(m_Registers[*VideoRegister::STAT] & 0x03); }
    void SetVideoMode(VideoState newMode) { m_Registers[*VideoRegister::STAT] = (m_Registers[*VideoRegister::STAT] & 0xFC) | static_cast<quint8>(newMode); }
    void ReadVideoRAM(GBBus* bus, bool modeOverride);
    void WriteVideoRAM(GBBus* bus);
    void ReadVideoRegister(GBBus* bus);
    void WriteVideoRegister(GBBus* bus);
	quint32 PerformCycle() override { return ++m_Cycles; }
	void SetState(IGBVideoState* newState) override;
	bool IsDisplayEnabled() override { return (m_Registers[*VideoRegister::LCDC] & 0x80) != 0; }
	void ResetCycles() override { m_Cycles = 0; }
	void IncreaseYLineCount() override { m_Registers[*VideoRegister::LY] = (m_Registers[*VideoRegister::LY] + 1) % VIDEO_MAX_Y_LINE_COUNT; }
	quint8 GetYLineCount() override { return m_Registers[*VideoRegister::LY]; }
public:
    GBVideo();
    ~GBVideo() override;
    void Reset() override;
    void Tick(GBBus* bus) override;
    void GetScreenSize(int& w, int& h) { w = SCREEN_WIDTH; h = SCREEN_HEIGHT; }
    quint32* GetFrame();
};

#endif // GBLCDDISPLAY_H
