#ifndef GBROM_H
#define GBROM_H

#include <QtGlobal>
#include "GBComponent.h"

#define BIOS_SIZE 0x0100
#define BIOS_MD5 "32fbbd84168d3482956eb3c5051637f5"
#define BIOS_UNMAP 0xFF50

class GBBios : public GBComponent
{
private:
    quint8 m_Data[BIOS_SIZE];
    bool m_IsBiosLoaded;
    bool m_IsBiosMapped;
public:
    GBBios();
    bool Load(QString biosFilePath);
    void Reset() override;
    void Tick(GBBus* bus) override;
};

#endif // GBROM_H
