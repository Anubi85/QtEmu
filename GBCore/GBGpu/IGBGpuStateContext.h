#pragma once

#include <QtGlobal>

#define SCREEN_WIDTH  160
#define SCREEN_HEIGHT 144
#define VIDEO_MAX_Y_LINE_COUNT 154

class IGBGpuState;

class IGBGpuStateContext
{
protected:
    IGBGpuStateContext();
public:
    virtual ~IGBGpuStateContext();
	virtual quint32 PerformCycle() = 0;
    virtual void SetState(IGBGpuState* newState) = 0;
	virtual bool IsDisplayEnabled() = 0;
	virtual void ResetCycles() = 0;
	virtual void IncreaseYLineCount() = 0;
	virtual quint8 GetYLineCount() = 0;
    virtual bool GetBackgroundTileMap() = 0;
    virtual bool GetBackgroundTileID() = 0;
    virtual quint8 GetYScroll() = 0;
    virtual quint8 GetXScroll() = 0;
    virtual void SetPixel(quint8 pixelIdx, quint8 pixelValue) = 0;
    virtual void FrameReady() = 0;
};
