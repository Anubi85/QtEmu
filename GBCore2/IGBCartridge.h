#ifndef IGBCARTRIDGE_H
#define IGBCARTRIDGE_H

#include <QtCore>
#include "GBComponent.h"

class IGBCartridge : public GBComponent
{
private:
    IGBCartridge();
public:
    virtual ~IGBCartridge() override;
    virtual void Reset() override = 0;
    virtual void Tick(GBBus* bus) override = 0;
    static IGBCartridge* Load(QString romFilePath);
};

#endif // IGBCARTRIDGE_H
