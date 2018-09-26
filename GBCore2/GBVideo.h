#ifndef GBLCDDISPLAY_H
#define GBLCDDISPLAY_H

#include "GBComponent.h"

#define VIDEO_REG_SIZE 0x000C
#define VIDEO_REG_ADDRESS_OFFSET 0xFF40
#define VIDEO_RAM_SIZE 0x2000
#define VIDEO_RAM_ADDRESS_OFFSET 0x8000

enum class VideoRegister
{

};

class GBVideo : public GBComponent
{
private:
    QByteArray m_Registers;
    QByteArray m_VideoRAM;

    bool IsAddressInVideoRAM(quint16 address) { return address >= VIDEO_RAM_ADDRESS_OFFSET && address < VIDEO_RAM_ADDRESS_OFFSET + VIDEO_RAM_SIZE; }
    bool IsAddressInVideoReg(quint16 address) { return address >= VIDEO_REG_ADDRESS_OFFSET && address < VIDEO_REG_ADDRESS_OFFSET + VIDEO_REG_SIZE; }
public:
    GBVideo();
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBLCDDISPLAY_H
