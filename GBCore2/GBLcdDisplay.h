#ifndef GBLCDDISPLAY_H
#define GBLCDDISPLAY_H

#include "GBComponent.h"

#define VIDEO_RAM_SIZE 0x2000
#define ADDRESS_OFFSET 0x8000

class GBLcdDisplay : public GBComponent
{
private:
    QByteArray m_VideoRAM;

    bool IsAddressInRange(quint16 address) { return address >= ADDRESS_OFFSET && address < ADDRESS_OFFSET + VIDEO_RAM_SIZE; }
public:
    GBLcdDisplay();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBLCDDISPLAY_H
