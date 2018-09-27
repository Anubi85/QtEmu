#include "GBCartridgeBehaviour_RomOnly.h"
#include "GBBus.h"

GBCartridgeBehaviour_RomOnly::GBCartridgeBehaviour_RomOnly(QByteArray data) :
    IGBCartridgeBehaviour(data)
{
    m_Data.resize(ROM_ONLY_SIZE);
}

void GBCartridgeBehaviour_RomOnly::ProcessRequests(GBBus* bus)
{
    if (bus->IsReadReqPending() && bus->GetAddress() < ROM_ONLY_SIZE)
    {
        bus->SetData(static_cast<quint8>(m_Data[bus->GetAddress()]));
        bus->ReadReqAck();
    }
}
