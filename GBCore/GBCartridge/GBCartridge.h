#pragma once

#include <QtGlobal>
#include "GBComponent.h"
#include "IGBCartridgeBehaviour.h"

#define CARTRIDGE_TYPE_ADDRESS 0x0147

enum class CartridgeType
{
    ROM_ONLY = 0x00,
};

class GBCartridge : public GBComponent
{
private:
    IGBCartridgeBehaviour* m_Behaviour;
public:
    GBCartridge() { m_Behaviour = nullptr; }
    ~GBCartridge() override { delete m_Behaviour; }
    void Reset() override;
    void Tick(GBBus* bus, GBInterruptBus* interruptBus) override;
    bool Load(QString romFilePath);
};
