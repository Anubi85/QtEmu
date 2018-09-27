#ifndef IGBCARTRIDGE_H
#define IGBCARTRIDGE_H

#include <QtCore>
#include "GBComponent.h"

#define CARTRIDGE_TYPE_ADDRESS 0x0147

enum class CartridgeType
{
    ROM_ONLY = 0x00,
};

class IGBCartridgeBehaviour;

class GBCartridge : public GBComponent
{
private:
    IGBCartridgeBehaviour* m_Behaviour;
public:
    GBCartridge();
    void Reset() override;
    void Tick(GBBus* bus) override;
    bool Load(QString romFilePath);
};

#endif // IGBCARTRIDGE_H
