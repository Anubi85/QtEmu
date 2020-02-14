#pragma once

#include <QtGlobal>

class GBCounter
{
private:
    quint32 m_Counter;
public:
    GBCounter() { m_Counter = 0; }
    void Reload(quint32 value) { m_Counter = value; }
    void Tick() { if (m_Counter > 0) m_Counter--; }
    bool IsZero(){ return m_Counter == 0; }
};
