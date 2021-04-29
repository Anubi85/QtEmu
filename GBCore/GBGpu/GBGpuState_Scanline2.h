#pragma once

#include <QtGlobal>
#include "IGBGpuState.h"

class GBGpuState_Scanline2 : public IGBGpuState
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
    GBGpuState_Scanline2(IGBGpuStateContext* context) : IGBGpuState(context) { }
    void Reset() override;
    void Tick(GBBus* bus) override;
    GpuState GetStateID() override { return GpuState::Scanline2; }
};
