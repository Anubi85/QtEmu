#ifndef IGBAUDIOCHANNELCONTEXT_H
#define IGBAUDIOCHANNELCONTEXT_H

#include <QtGlobal>

class IGBAudioChannelContext
{
protected:
    IGBAudioChannelContext();
public:
    virtual ~IGBAudioChannelContext();
    virtual quint8 GetRegister(quint16 address);
    virtual void SetRegister(quint16 address, quint8 value);
};

#endif // IGBAUDIOCHANNELCONTEXT_H
