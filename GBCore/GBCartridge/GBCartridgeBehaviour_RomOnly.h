#ifndef GBCARTRIDGEBEHAVIOUR_ROMONLY_H
#define GBCARTRIDGEBEHAVIOUR_ROMONLY_H

#include <QtGlobal>
#include "IGBCartridgeBehaviour.h"

#define ROM_ONLY_SIZE 0x8000

class GBBus;

class GBCartridgeBehaviour_RomOnly : public IGBCartridgeBehaviour
{
public:
    GBCartridgeBehaviour_RomOnly(quint8* data);
    void ProcessRequests(GBBus* bus) override;
};

#endif // GBCARTRIDGEBEHAVIOUR_ROMONLY_H
