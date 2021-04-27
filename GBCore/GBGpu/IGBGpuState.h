#pragma once

enum class VideoState
{
    HBlank = 0x00,
    VBlank = 0x01,
    Scanline1 = 0x02,
    Scanline2 = 0x03,
    Suspended
};

class IGBGpuStateContext;
class GBBus;

class IGBGpuState
{
protected:
    IGBGpuStateContext* m_Context;
    IGBGpuState(IGBGpuStateContext* context);
public:
    virtual ~IGBGpuState();
    virtual void Tick(GBBus* bus) = 0;
    virtual VideoState GetStateID() = 0;
};
