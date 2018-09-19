#ifndef GBLCDDISPLAY_H
#define GBLCDDISPLAY_H

#include "GBComponent.h"

#define VIDEO_RAM_SIZE 0x2000
#define VIDEO_ADDRESS_OFFSET 0x8000

class GBLcdDisplay : public GBComponent
{
private:
    QByteArray m_VideoRAM;

    bool IsAddressInRange(quint16 address) { return address >= VIDEO_ADDRESS_OFFSET && address < VIDEO_ADDRESS_OFFSET + VIDEO_RAM_SIZE; }
public:
    GBLcdDisplay();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBLCDDISPLAY_H
