#include "GBAudio.h"
#include "GBBus.h"

GBAudio::GBAudio()
{
    Reset();
}

void GBAudio::Reset()
{
    GBComponent::Reset();
    memset(m_Registers, 0, AUDIO_MEMORY_SIZE);
    m_AudioChannel2.Reset();
}

void GBAudio::Tick(GBBus* bus)
{
    AudioRegister reg;
    quint8 mask;
    //check if a read request is pending and the address is in range
    if (bus->IsReadReqPending() && IsAddressInRange(bus->GetAddress()))
    {
        reg = static_cast<AudioRegister>(bus->GetAddress() - AUDIO_ADDRESS_OFFSET);
        switch (reg)
        {
        case AudioRegister::NR11:
            mask = 0x3F;
            break;
        case AudioRegister::NR12:
            mask = 0x00;
            break;
        case AudioRegister::NR13:
            mask = 0xFF;
            break;
        case AudioRegister::NR14:
            mask = 0xBF;
            break;
        case AudioRegister::NR50:
            mask = 0x00;
            break;
        case AudioRegister::NR51:
            mask = 0x00;
            break;
        case AudioRegister::NR52:
            mask = 0x70;
            break;
        default:
            return;
        }
        bus->SetData(m_Registers[*reg] | mask);
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
        m_AudioChannel2.Tick(bus);
        //mix audio channels
        //generate right and left output
        //apply master volume
    }
}
