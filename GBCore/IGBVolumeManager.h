#ifndef IGBVOLUMEMANAGER_H
#define IGBVOLUMEMANAGER_H

#include <QtGlobal>

class IGBVolumeManager
{
protected:
    quint8 m_Sample;
    bool m_IsEnabled;
    quint8* m_Registers;

    IGBVolumeManager(quint8* registers);
public:
    virtual ~IGBVolumeManager();
    virtual void Reset();
    virtual void Tick(quint8 sample) = 0;
    quint8 GetSample() { return m_Sample; }
    bool IsEnabled() { return m_IsEnabled; }
};

#endif // IGBVOLUMEMANAGER_H
