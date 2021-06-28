#pragma once

#include <QtGlobal>
#include "GBComponent.h"

class GBSerial : public GBComponent
{
private:
    quint8 m_SB;
    quint8 m_SC;
    bool m_IsTransferingData;
    quint8 m_BitCounter;
public:
    GBSerial() { Reset(); }
    void Reset() override;
    void Tick(GBBus* bus, GBInterruptBus* interruptBus) override;
};
