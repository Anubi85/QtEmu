#ifndef GBAUDIOMODULE_ENVELOPEVOLUMEMANAGER_H
#define GBAUDIOMODULE_ENVELOPEVOLUMEMANAGER_H

#include <QtGlobal>
#include "IGBAudioModule.h"

class GBAudioModule_EnvelopeVolumeManager : public IGBAudioModule
{
private:
    quint8 m_Counter;
    bool m_UpdateVolume;
public:
    GBAudioModule_EnvelopeVolumeManager(quint8* registers);
    void Reset() override;
    void Tick() override;
    void Trigger() override;
};

#endif // GBAUDIOMODULE_ENVELOPEVOLUMEMANAGER_H
