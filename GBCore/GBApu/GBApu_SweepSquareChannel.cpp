#include "GBInternalBus.h"
#include "GBApu_SweepSquareChannel.h"
#include "GBApu_FrequencySweepModule.h"
#include "GBApu_SquareWaveModule.h"
#include "GBApu_LengthCounterModule.h"
#include "GBApu_VolumeEnvelopeModule.h"

GBApu_SweepSquareChannel::GBApu_SweepSquareChannel(quint8& apuStatus) :
		GBApu_ChannelBase(AUDIO_CHANNEL1_ENABLE_MASK, APU_REGISTERS_ADDRESS, apuStatus)
{
    m_Modules[0] = new GBApu_FrequencySweepModule(c_ChannelMask, m_ApuStatus, m_Registers);
    m_Modules[1] = new GBApu_SquareWaveModule(m_Registers);
    m_Modules[2] = new GBApu_LengthCounterModule(0x3F, c_ChannelMask, m_ApuStatus, m_Registers);
    m_Modules[3] = new GBApu_VolumeEnvelopeModule(m_Registers);
}

void GBApu_SweepSquareChannel::ReadRegister(IGBBus* bus)
{
	switch (bus->GetAddress())
	{
		case NR10_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)] | 0x80);
			break;
		case NR11_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)] | 0x3F);
			break;
		case NR12_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)]);
			break;
		case NR13_REGISTER:
			bus->SetData(0xFF);
			break;
		case NR14_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)] | 0xBF);
			break;
		default:
			return;
	}
	bus->ReadReqAck();
}

void GBApu_SweepSquareChannel::WriteRegister(IGBBus* bus)
{
	switch (bus->GetAddress())
	{
		case NR10_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData() & 0x7F;
			break;
		case NR11_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData();
			break;
		case NR12_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData();
			break;
		case NR13_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData();
			break;
		case NR14_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData() & 0xC7;
			Trigger();
			break;
		default:
			return;
	}
	bus->WriteReqAck();
}
