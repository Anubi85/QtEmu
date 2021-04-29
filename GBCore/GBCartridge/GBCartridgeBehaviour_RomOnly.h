#pragma once

#include <QtGlobal>
#include "IGBCartridgeBehaviour.h"

#define ROM_ONLY_SIZE 0x8000

class GBBus;

class GBCartridgeBehaviour_RomOnly : public IGBCartridgeBehaviour
{
public:
    GBCartridgeBehaviour_RomOnly(quint8* data) : IGBCartridgeBehaviour(data, ROM_ONLY_SIZE) { }
    void ProcessRequests(GBBus* bus) override;
};
