#ifndef IEMULATORCORE_H
#define IEMULATORCORE_H

#include <QtCore>

class IEmulatorCore
{
public:
    virtual ~IEmulatorCore() {}
    virtual bool LoadBios(QString biosFilePath) = 0;
    virtual void Exec() = 0;
};

#endif //IEMULATORCORE_H
