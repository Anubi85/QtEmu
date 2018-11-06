#ifndef GBVOLUMEMANAGER_ENVELOPE_H
#define GBVOLUMEMANAGER_ENVELOPE_H

#include <QtGlobal>
#include "IGBVolumeManager.h"

class GBVolumeManager_Envelope : public IGBVolumeManager
{
private:
    quint8 m_Counter;
    quint8 m_Volume;
    bool m_UpdateVolume;
public:
    GBVolumeManager_Envelope(quint8* registers);
    void Reset() override;
    void Tick(quint8 sample) override;
};

#endif // GBVOLUMEMANAGER_ENVELOPE_H
