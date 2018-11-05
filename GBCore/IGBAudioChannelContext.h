#ifndef IGBAUDIOCHANNELCONTEXT_H
#define IGBAUDIOCHANNELCONTEXT_H

#include <QtGlobal>

class IGBAudioChannelContext
{
protected:
    IGBAudioChannelContext();
public:
    virtual ~IGBAudioChannelContext();
    virtual quint8 GetRegister(quint16 address)
    {
        Q_UNUSED(address)
        return 0xFF;
    }
    virtual void SetRegister(quint16 address, quint8 value)
    {
        Q_UNUSED(address)
        Q_UNUSED(value)
    }
};

#endif // IGBAUDIOCHANNELCONTEXT_H
