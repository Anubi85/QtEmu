#include "GBApu_ChannelBase.h"

GBApu_ChannelBase::GBApu_ChannelBase(quint16 startRegAddress, quint8& apuStatus) :
	c_StartRegAddress(startRegAddress),
	m_ApuStatus(apuStatus)
{
	m_Dac = new GBApu_Dac(m_Sample);
	Reset();
}

GBApu_ChannelBase::~GBApu_ChannelBase()
{
	delete m_Dac;
}

void GBApu_ChannelBase::Reset()
{
	memset(m_Registers, 0, AUDIO_CHANNEL_REG_NUM);
	m_Sample = 0;
}
