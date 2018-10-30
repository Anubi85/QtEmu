#include "GBAudio.h"
#include "GBBus.h"
#include "GBWaveGenerator_Square.h"

GBAudio::GBAudio() :
    m_AudioChannel2(this, new GBWaveGenerator_Square())
{
    Reset();
}

void GBAudio::Reset()
{
    GBComponent::Reset();
    memset(m_Registers, 0, AUDIO_MEMORY_SIZE);
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

}

void GBAudio::Tick(GBBus* bus)
{
    AudioRegister reg;
    quint8 mask;
    //check if a read request is pending and the address is in range
    if (bus->IsReadReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        bus->SetData(ReadAudioRegister(static_cast<quint8>(bus->GetAddress() - AUDIO_ADDRESS_OFFSET)));
        bus->ReadReqAck();
    }
    //check if a write request is pending and the address is in range
    if (bus->IsWriteReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        reg = static_cast<AudioRegister>(bus->GetAddress() - AUDIO_ADDRESS_OFFSET);
        switch (reg)
        {
        case AudioRegister::NR11:
            mask = 0xFF;
            break;
        case AudioRegister::NR12:
            mask = 0xFF;
            break;
        case AudioRegister::NR13:
            mask = 0xFF;
            break;
        case AudioRegister::NR14:
            mask = 0xC7;
            break;
        case AudioRegister::NR50:
            mask = 0xFF;
            break;
        case AudioRegister::NR51:
            mask = 0xFF;
            break;
        case AudioRegister::NR52:
            mask = 0x80;
            break;
        default:
            return;
        }
        m_Registers[*reg] = bus->GetData() & mask;
        bus->WriteReqAck();
    }
    if (IsAudioEnabled())
    {
        //mix audio channels
        //generate right and left output
        //apply master volume
    }
}
