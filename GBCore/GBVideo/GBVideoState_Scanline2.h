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
    quint8 m_FineXScroll;
    quint8 m_FineYScroll;
    quint8 m_TileByte1;
    quint8 m_TileByte2;
    quint8 m_NewTileByte1;
    quint8 m_NewTileByte2;

    quint16 GetBackgroundTileAddress() { return m_BaseBackgroundTileMapAddress | m_XScroll; }
    quint16 GetBackgroundTileDataAddress(quint8 tileID);
public:
	GBVideoState_Scanline2(IGBVideoStateContext* context);
    void Tick(GBBus* bus) override;
    VideoState GetStateID() override { return VideoState::Scanline2; }
};

#endif // GBVIDEOSTATE_SCANLINE2_H
