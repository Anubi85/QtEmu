#include "GBAudio.h"
#include "GBBus.h"
#include "GBAudioModule_FrequencySweeper.h"
#include "GBAudioModule_SquareWaveGenerator.h"
#include "GBAudioModule_LengthCounter.h"

GBAudio::GBAudio()
{
    m_AudioChannel1 = GBAudioChannel::GetSweepSquareChannel(0x01, &m_Registers[*AudioRegister::NR52], m_Registers);
    m_AudioChannel2 = GBAudioChannel::GetSquareChannel(0x02, &m_Registers[*AudioRegister::NR52], m_Registers + AUDIO_CHANNEL_REG_NUM);
    m_AudioChannel3 = GBAudioChannel::GetWaveChannel(0x04, &m_Registers[*AudioRegister::NR52], m_Registers + 2 * AUDIO_CHANNEL_REG_NUM, m_Registers + AUDIO_SAMPLES_RAM_OFFSET);
    m_AudioChannel4 = GBAudioChannel::GetNoiseChannel(0x08, &m_Registers[*AudioRegister::NR52], m_Registers + 3 * AUDIO_CHANNEL_REG_NUM);
	m_AudioMixer = new GBAudioMixer(&m_Registers[*AudioRegister::NR51], &m_Registers[*AudioRegister::NR50]);
    Reset();
	InitSamplesRam();
}

GBAudio::~GBAudio()
{
    delete m_AudioChannel1;
    delete m_AudioChannel2;
    delete m_AudioChannel3;
	delete m_AudioChannel4;
	delete m_AudioMixer;
}

void GBAudio::Reset()
{
    GBComponent::Reset();
	memset(m_Registers, 0, AUDIO_SAMPLES_RAM_OFFSET);
    m_AudioChannel1->Reset();
    m_AudioChannel2->Reset();
    m_AudioChannel3->Reset();
    m_AudioChannel4->Reset();
}

void GBAudio::InitSamplesRam()
{
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0x0] = 0x84;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0x1] = 0x40;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0x2] = 0x43;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0x3] = 0xAA;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0x4] = 0x2D;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0x5] = 0x78;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0x6] = 0x92;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0x7] = 0x3C;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0x8] = 0x60;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0x9] = 0x59;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0xA] = 0x59;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0xB] = 0xB0;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0xC] = 0x34;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0xD] = 0xB8;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0xE] = 0x2E;
	m_Registers[AUDIO_SAMPLES_RAM_OFFSET + 0xF] = 0xDA;
}

bool GBAudio::IsSamplesRamRegister(quint8 regAddress)
{
	return regAddress >= AUDIO_SAMPLES_RAM_OFFSET;
}

quint8 GBAudio::ReadAudioRegister(quint8 regAddress)
{
	switch (regAddress)
	{
	case *AudioRegister::NR10:
		return m_Registers[regAddress] | 0x80;
	case *AudioRegister::NR11:
	case *AudioRegister::NR21:
		return m_Registers[regAddress] | 0x3F;
	case *AudioRegister::NR12:
	case *AudioRegister::NR22:
	case *AudioRegister::NR42:
	case *AudioRegister::NR43:
	case *AudioRegister::NR50:
	case *AudioRegister::NR51:
		return m_Registers[regAddress];
	case *AudioRegister::NR13:
	case *AudioRegister::NR23:
	case *AudioRegister::NR31:
	case *AudioRegister::NR33:
	case *AudioRegister::NR41:
		return 0xFF;
	case *AudioRegister::NR14:
	case *AudioRegister::NR24:
	case *AudioRegister::NR34:
	case *AudioRegister::NR44:
		return m_Registers[regAddress] | 0xBF;
	case *AudioRegister::NR30:
		return m_Registers[regAddress] | 0x7F;
	case *AudioRegister::NR32:
		return m_Registers[regAddress] | 0x9F;
	case *AudioRegister::NR52:
		return m_Registers[regAddress] | 0x70;
	default:
		return 0xFF;
	}
}

void GBAudio::WriteAudioRegister(quint8 regAddress, quint8 value)
{
	if (IsAudioEnabled() || IsSamplesRamRegister(regAddress))
	{
		switch (regAddress)
		{
		case *AudioRegister::NR10:
			m_Registers[regAddress] = value & 0x7F;
			break;
		case *AudioRegister::NR11:
		case *AudioRegister::NR12:
		case *AudioRegister::NR13:
		case *AudioRegister::NR21:
		case *AudioRegister::NR22:
		case *AudioRegister::NR23:
		case *AudioRegister::NR31:
		case *AudioRegister::NR33:
		case *AudioRegister::NR42:
		case *AudioRegister::NR43:
		case *AudioRegister::NR50:
		case *AudioRegister::NR51:
			m_Registers[regAddress] = value;
			break;
		case *AudioRegister::NR30:
			m_Registers[regAddress] = value & 0x80;
			break;
		case *AudioRegister::NR32:
			m_Registers[regAddress] = value & 0x60;
			break;
		case *AudioRegister::NR41:
			m_Registers[regAddress] = value & 0x3F;
			break;
		case *AudioRegister::NR14:
			m_Registers[regAddress] = value & 0xC7;
			m_AudioChannel1->Trigger();
			break;
		case *AudioRegister::NR24:
			m_Registers[regAddress] = value & 0xC7;
			m_AudioChannel2->Trigger();
			break;
		case *AudioRegister::NR34:
			m_Registers[regAddress] = value & 0xC7;
			m_AudioChannel3->Trigger();
			break;
		case *AudioRegister::NR44:
			m_Registers[regAddress] = value & 0xC0;
			m_AudioChannel4->Trigger();
			break;
		case *AudioRegister::NR52:
			m_Registers[regAddress] &= 0x7F;
			m_Registers[regAddress] |= value & 0x80;
			if (!IsAudioEnabled())
			{
				Reset();
			}
			break;
		default:
			break;
		}
	}
}

void GBAudio::Tick(GBBus* bus)
{
    //check if a read request is pending and the address is in range
	if (bus->IsReadReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        bus->SetData(ReadAudioRegister(static_cast<quint8>(bus->GetAddress() - AUDIO_ADDRESS_OFFSET)));
        bus->ReadReqAck();
    }
    //check if a write request is pending and the address is in range
    if (bus->IsWriteReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        WriteAudioRegister(static_cast<quint8>(bus->GetAddress() - AUDIO_ADDRESS_OFFSET), bus->GetData());
        bus->WriteReqAck();
    }
    if (IsAudioEnabled())
    {
        m_AudioChannel1->Tick();
        m_AudioChannel2->Tick();
        m_AudioChannel3->Tick();
        m_AudioChannel4->Tick();
		m_AudioMixer->Tick(
					m_AudioChannel1->GetSample(),
					m_AudioChannel2->GetSample(),
					m_AudioChannel3->GetSample(),
					m_AudioChannel4->GetSample(),
					1.0); //TODO: Modify with master volume
		//Output samples
    }
}
