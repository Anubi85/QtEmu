#pragma once

#include <QtGlobal>
#include "IGBGpuState.h"

#define SCREEN_WIDTH  160
#define SCREEN_HEIGHT 144
#define VIDEO_MAX_Y_LINE_COUNT 154

class IGBGpuStateContext
{
protected:
    IGBGpuStateContext() { }
public:
    virtual ~IGBGpuStateContext() { }
	virtual quint32 PerformCycle() = 0;
    virtual void SetState(GpuState newStateId) = 0;
	virtual bool IsDisplayEnabled() = 0;
	virtual bool IsBackgroundEnabled() = 0;
	virtual bool IsWindowEnabled() = 0;
	virtual void ResetCycles() = 0;
	virtual void IncreaseYLineCount() = 0;
	virtual void IncreaseWindowLineCount() = 0;
	virtual void ResetWindowLineCount() = 0;
	virtual quint8 GetYLineCount() = 0;
	virtual quint8 GetWindowLineCount() = 0;
	virtual quint8 GetWindowYCoord() = 0;
	virtual quint8 GetWindowXCoord() = 0;
	virtual bool IsWindowActive() = 0;
	virtual void ActivateWindow(bool activate) = 0;
    virtual bool GetBackgroundTileMap() = 0;
	virtual bool GetWindowTileMap() = 0;
	virtual bool GetTileID() = 0;
    virtual quint8 GetYScroll() = 0;
    virtual quint8 GetXScroll() = 0;
    virtual void SetPixel(quint8 pixelIdx, quint8 pixelValue) = 0;
    virtual void FrameReady() = 0;
};
