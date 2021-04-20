#pragma once

#include <QtGlobal>

class GBBus
{
private:
    quint16 m_Address;
    quint8 m_Data;
	bool m_WriteReq;
    bool m_ReadReq;
public:
    GBBus();
    void Clear();
    void SetAddress(quint16 address) { m_Address = address; }
    quint16 GetAddress() { return m_Address; }
	quint16 GetLocalAddress(quint16 offset) { return	m_Address - offset; }
    void SetData(quint8 data) { m_Data = data; }
    quint8 GetData() { return m_Data; }
    void RequestWrite() { m_WriteReq = !m_ReadReq; } //allow write request only if no read request are pending
    void WriteReqAck() { m_WriteReq = false; }
    void RequestRead() { m_ReadReq = !m_WriteReq; } //allow read request only if no write request are pending
    void ReadReqAck() { m_ReadReq = false; }
    bool IsWriteReqPending() { return m_WriteReq; }
    bool IsReadReqPending() {return m_ReadReq; }
};
