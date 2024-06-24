#pragma once

#include <QtGlobal>

class IGBBus
{
public:
	virtual ~IGBBus() { }
	virtual void SetAddress(quint16 address) = 0;
	virtual quint16 GetAddress() = 0;
	virtual quint16 GetLocalAddress(quint16 offset) = 0;
	virtual void SetData(quint8 data) = 0;
	virtual quint8 GetData() = 0;
	virtual void RequestWrite() = 0;
	virtual void WriteReqAck() = 0;
	virtual void RequestRead() = 0;
	virtual void ReadReqAck() = 0;
	virtual bool IsWriteReqPending() = 0;
	virtual bool IsReadReqPending() = 0;
};
