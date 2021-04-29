#pragma once

#include <QtGlobal>

class GBBus;

class IGBCartridgeBehaviour
{
protected:
    quint8* m_Data;
    quint32 m_DataSize;
    IGBCartridgeBehaviour(quint8* data, quint32 size);
public:
    virtual ~IGBCartridgeBehaviour() { delete[] m_Data; }
    virtual void ProcessRequests(GBBus* bus) = 0;
};
