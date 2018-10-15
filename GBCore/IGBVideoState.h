#ifndef IGBVIDEOSTATE_H
#define IGBVIDEOSTATE_H

enum class VideoState
{
    HBlank = 0x00,
    VBlank = 0x01,
    Scanline1 = 0x02,
    Scanline2 = 0x03,
    Suspended
};

class IGBVideoStateContext;
class GBBus;

class IGBVideoState
{
protected:
	IGBVideoStateContext* m_Context;
	IGBVideoState(IGBVideoStateContext* context);
public:
    virtual ~IGBVideoState();
    virtual void Tick(GBBus* bus) = 0;
    virtual VideoState GetStateID() = 0;
};

#endif // IGBVIDEOSTATE_H
