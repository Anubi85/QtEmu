#ifndef IEMULATORCORE_H
#define IEMULATORCORE_H

#include <QtCore>

class IEmulatorCore
{
public:
    virtual ~IEmulatorCore() = default;
    virtual void Exec() = 0;
    virtual bool HasError() = 0;
    virtual void GetScreenSize(int& width, int& height) = 0;
    virtual bool Initialize(QString biosFilePath, QString romFilePath) = 0;
    virtual quint32* GetFrame() = 0;
};

#endif //IEMULATORCORE_H
