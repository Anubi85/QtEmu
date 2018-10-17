#ifndef GBVIDEOSTATE_SCANLINE2_H
#define GBVIDEOSTATE_SCANLINE2_H

#include <QtGlobal>
#include "IGBVideoState.h"

class GBVideoState_Scanline2 : public IGBVideoState
{
private:
    qint16 m_Count;
    quint8 m_PixelCount;
    quint16 m_BaseBackgroundTileMapAddress;
    quint8 m_XScroll;

    quint16 GetBackgroundTileAddress() { return m_BaseBackgroundTileMapAddress | m_XScroll++; };
public:
	GBVideoState_Scanline2(IGBVideoStateContext* context);
    void Tick(GBBus* bus) override;
    VideoState GetStateID() override { return VideoState::Scanline2; }
};

#endif // GBVIDEOSTATE_SCANLINE2_H
