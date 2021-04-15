#ifndef IGBAUDIOMODULE_H
#define IGBAUDIOMODULE_H

#include <QtGlobal>

class IGBAudioModule
{
protected:
    bool m_Enabled;
    quint8 m_Sample;
    quint8* m_Registers;

    IGBAudioModule(quint8* registers);
public:
    virtual ~IGBAudioModule();
    virtual void Reset();
    virtual void Tick() = 0;
    virtual void Trigger() = 0;
    bool IsEnabled() { return m_Enabled; }
    quint8 GetSample() { return m_Sample; }
};

#endif // IGBAUDIOMODULE_H
