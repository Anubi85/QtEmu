#ifndef GBVIDEOSTATE_SCANLINE2_H
#define GBVIDEOSTATE_SCANLINE2_H

#include <QtGlobal>
#include "IGBVideoState.h"

class GBVideoState_Scanline2 : public IGBVideoState
{
private:
    qint16 m_Count;
    quint8 m_PixelCount;
public:
	GBVideoState_Scanline2(IGBVideoStateContext* context);
    void Tick(GBBus* bus) override;
    VideoState GetStateID() override { return VideoState::Scanline2; }
};

#endif // GBVIDEOSTATE_SCANLINE2_H
