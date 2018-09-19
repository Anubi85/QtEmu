#ifndef GBLCDDISPLAY_H
#define GBLCDDISPLAY_H

#include "GBComponent.h"

#define VIDEO_RAM_SIZE 0x2000
#define ADDRESS_OFFSET 0x8000

class GBLcdDisplay : public GBComponent
{
private:
    QByteArray m_VideoRAM;
public:
    GBLcdDisplay();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBLCDDISPLAY_H
