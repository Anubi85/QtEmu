#pragma once

#include "IGBBus.h"
#include "GBMemoryMap.h"

struct GBSharedBusData
{
	bool IsDmaActive;
	quint16 MainAddress;
	quint16 DmaAddress;
	quint8 MainData;
	quint8 DmaData;
};

class GBSharedBus : public IGBBus
{
private:
	bool m_IsDmaBus;
	GBSharedBusData& m_BusData;
	bool m_WriteReq;
	bool m_ReadReq;
public:
	GBSharedBus(bool isDmaBus, GBSharedBusData& busData);
	~GBSharedBus() override;
	void Clear();
	bool IsAddressInDmaRange() { return m_BusData.MainAddress < IO_REGISTERS_ADDRESS; }
	void SetAddress(quint16 address) override;
	quint16 GetAddress() override;
	quint16 GetLocalAddress(quint16 offset) override { return GetAddress() - offset; }
	void SetData(quint8 data) override;
	quint8 GetData() override;
	void RequestWrite() override;
	void WriteReqAck() override { m_WriteReq = false; }
	void RequestRead() override;
	void ReadReqAck() override { m_ReadReq = false; }
	bool IsWriteReqPending() override { return m_WriteReq; }
	bool IsReadReqPending() override { return m_ReadReq; }
};
