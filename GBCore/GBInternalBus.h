#pragma once

#include "IGBBus.h"

class GBInternalBus : public IGBBus
{
private:
	quint16 m_Address;
	quint8 m_Data;
	bool m_WriteReq;
	bool m_ReadReq;
public:
	GBInternalBus() { Clear(); }
	~GBInternalBus() override { }
	void Clear();
	void SetAddress(quint16 address) override { m_Address = address; }
	quint16 GetAddress() override { return m_Address; }
	quint16 GetLocalAddress(quint16 offset) override { return m_Address - offset; }
	void SetData(quint8 data) override { m_Data = data; }
	quint8 GetData() override { return m_Data; }
	void RequestWrite() override { m_WriteReq = !m_ReadReq; } //allow write request only if no read request are pending
	void WriteReqAck() override { m_WriteReq = false; }
	void RequestRead() override { m_ReadReq = !m_WriteReq; } //allow read request only if no write request are pending
	void ReadReqAck() override { m_ReadReq = false; }
	bool IsWriteReqPending() override { return m_WriteReq; }
	bool IsReadReqPending() override {return m_ReadReq; }
};
