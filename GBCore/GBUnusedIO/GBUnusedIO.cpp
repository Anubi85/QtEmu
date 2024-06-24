#include "GBUnusedIO.h"
#include "GBBus.h"

void GBUnusedIO::Reset()
{
	GBComponent::Reset();
}

bool GBUnusedIO::IsAddressInRange(quint16 address)
{
	return (address > SC_REGISTER && address < DIV_REGISTER) ||
			(address > TAC_REGISTER && address < NR10_REGISTER) ||
			(address > NR52_REGISTER && address < APU_RAM_ADDRESS) ||
			(address >= IO_UNUSED_REGISTERS_ADDRESS && address < IO_UNUSED_REGISTERS_ADDRESS + IO_UNUSED_REGISTERS_SIZE);
}

void GBUnusedIO::Tick(GBBus* bus)
{
	if (IsAddressInRange(bus->MainBus()->GetAddress()))
	{
		if (bus->MainBus()->IsReadReqPending())
		{
			bus->MainBus()->SetData(0xFF);
			bus->MainBus()->ReadReqAck();
		}
		if (bus->MainBus()->IsWriteReqPending())
		{
			bus->MainBus()->WriteReqAck();
		}
	}
}
