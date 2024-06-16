#pragma once

#include <QtGlobal>
#include "IGBGpuState.h"

class GBGpuState_Scanline2 : public IGBGpuState
{
private:
	qint8 m_FetcherStepCount;
    quint8 m_PixelCount;
	quint16 m_BaseBackgroundTileMapAddress;
	quint16 m_BaseWindowTileMapAddress;
	quint16 m_TileMapAddress;
    quint8 m_XScroll;
    quint8 m_FineXScroll;
	quint8 m_FineBackgroundYScroll;
	quint8 m_FineWindowYScroll;
    quint8 m_TileByte1;
    quint8 m_TileByte2;
    quint8 m_NewTileByte1;
    quint8 m_NewTileByte2;
	quint8 m_AvailablePixels;
	bool m_FetchWindow;

	quint16 GetTileDataAddress(quint8 tileID);
public:
    GBGpuState_Scanline2(IGBGpuStateContext* context) : IGBGpuState(context) { }
    void Reset() override;
    void Tick(GBBus* bus) override;
    GpuState GetStateID() override { return GpuState::Scanline2; }
};
