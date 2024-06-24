#include "GBSharedBus.h"

GBSharedBus::GBSharedBus(bool isDmaBus, GBSharedBusData& busData) :
	m_BusData(busData)
{
	m_IsDmaBus = isDmaBus;
}

GBSharedBus::~GBSharedBus() { }

void GBSharedBus::Clear()
{
	m_ReadReq = false;
	m_WriteReq = false;
}

void GBSharedBus::SetAddress(quint16 address)
{
	m_IsDmaBus ? m_BusData.DmaAddress = address : m_BusData.MainAddress = address;
}

quint16 GBSharedBus::GetAddress()
{
	if (m_IsDmaBus)
	{
		return m_BusData.DmaAddress;
	}
	else if (m_BusData.IsDmaActive && IsAddressInDmaRange())
	{
		return m_BusData.DmaAddress;
	}
	else
	{
		return m_BusData.MainAddress;
	}
}

void GBSharedBus::SetData(quint8 data)
{
	m_IsDmaBus ? m_BusData.DmaData = data : m_BusData.MainData = data;
}

quint8 GBSharedBus::GetData()
{
	if (m_IsDmaBus)
	{
		return m_BusData.DmaData;
	}
	else if(m_BusData.IsDmaActive && IsAddressInDmaRange())
	{
		return m_BusData.DmaData;
	}
	else
	{
		return m_BusData.MainData;
	}
}

void GBSharedBus::RequestWrite()
{
	if (m_IsDmaBus ||
		(!m_IsDmaBus && !m_BusData.IsDmaActive) ||
		(!m_IsDmaBus && m_BusData.IsDmaActive && !IsAddressInDmaRange()))
	{
		//allow write request only if no read request are pending
		m_WriteReq = !m_ReadReq;
	}
}

void GBSharedBus::RequestRead()
{
	if (m_IsDmaBus ||
		(!m_IsDmaBus && !m_BusData.IsDmaActive) ||
		(!m_IsDmaBus && m_BusData.IsDmaActive && !IsAddressInDmaRange()))
	{
		//allow read request only if no write request are pending
		m_ReadReq = !m_WriteReq;
	}
}
