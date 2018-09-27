#ifndef IGBCARTRIDGEBEHAVIOUR_H
#define IGBCARTRIDGEBEHAVIOUR_H

#include <QtCore>

class GBBus;

class IGBCartridgeBehaviour
{
protected:
    QByteArray m_Data;
    IGBCartridgeBehaviour(QByteArray data);
public:
    virtual ~IGBCartridgeBehaviour();
    virtual void ProcessRequests(GBBus* bus) = 0;
};

#endif // IGBCARTRIDGEBEHAVIOUR_H
