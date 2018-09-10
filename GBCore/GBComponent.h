#ifndef GBCOMPONENT_H
#define GBCOMPONENT_H

#include <QtCore>

class GBComponent
{
protected:
    quint32 m_ErrorCode;
public:
    GBComponent();
    virtual ~GBComponent();
    bool HasError() { return m_ErrorCode != 0; }
    virtual void Reset() = 0;
};

#endif // GBCOMPONENT_H
