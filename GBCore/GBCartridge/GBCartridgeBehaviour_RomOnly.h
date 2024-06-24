#pragma once

#include <QtGlobal>
#include "IGBCartridgeBehaviour.h"

class IGBBus;

class GBCartridgeBehaviour_RomOnly : public IGBCartridgeBehaviour
{
public:
    GBCartridgeBehaviour_RomOnly(quint8* data) : IGBCartridgeBehaviour(data, ROM_ONLY_SIZE) { }
	void ProcessRomRequests(IGBBus* bus);
	void ProcessRequests(GBBus* bus) override;
};
