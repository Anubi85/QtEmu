#include "GBInternalBus.h"
#include "GBApu_NoiseChannel.h"
#include "GBApu_LfsrModule.h"
#include "GBApu_LengthCounterModule.h"
#include "GBApu_VolumeEnvelopeModule.h"

GBApu_NoiseChannel::GBApu_NoiseChannel(quint8& apuStatus) :
	GBApu_ChannelBase(AUDIO_CHANNEL4_ENABLE_MASK, APU_REGISTERS_ADDRESS + 3 * AUDIO_CHANNEL_REG_NUM, apuStatus)
{
    m_Modules[0] = nullptr;
    m_Modules[1] = new GBApu_LfsrModule(m_Registers);
    m_Modules[2] = new GBApu_LengthCounterModule(0x3F, c_ChannelMask, m_ApuStatus, m_Registers);
    m_Modules[3] = new GBApu_VolumeEnvelopeModule(m_Registers);
}

void GBApu_NoiseChannel::ReadRegister(IGBBus* bus)
{
	switch (bus->GetAddress())
    {
		case NR40_REGISTER:
            bus->SetData(0xFF);
            break;
		case NR41_REGISTER:
            bus->SetData(0xFF);
            break;
		case NR42_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)]);
            break;
		case NR43_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)]);
            break;
		case NR44_REGISTER:
			bus->SetData(m_Registers[bus->GetLocalAddress(c_StartRegAddress)] | 0xBF);
            break;
        default:
            return;
    }
    bus->ReadReqAck();
}

void GBApu_NoiseChannel::WriteRegister(IGBBus* bus)
{
	switch (bus->GetAddress())
    {
		case NR40_REGISTER:
            //Not useed, do nothing
            break;
		case NR41_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData() & 0x3F;
            break;
		case NR42_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData();
            break;
		case NR43_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData();
            break;
		case NR44_REGISTER:
			m_Registers[bus->GetLocalAddress(c_StartRegAddress)] = bus->GetData() & 0xC0;
            Trigger();
            break;
        default:
            return;
    }
    bus->WriteReqAck();
}
