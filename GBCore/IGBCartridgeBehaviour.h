#ifndef IGBCARTRIDGEBEHAVIOUR_H
#define IGBCARTRIDGEBEHAVIOUR_H

#include <QtCore>

class GBBus;

class IGBCartridgeBehaviour
{
protected:
    quint8* m_Data;
    quint32 m_DataSize;
    IGBCartridgeBehaviour(quint8* data, quint32 size);
public:
    virtual ~IGBCartridgeBehaviour();
    virtual void ProcessRequests(GBBus* bus) = 0;
};

#endif // IGBCARTRIDGEBEHAVIOUR_H
