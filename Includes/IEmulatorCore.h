#ifndef IEMULATORCORE_H
#define IEMULATORCORE_H

#include <QtCore>

class IEmulatorCore
{
public:
    virtual ~IEmulatorCore() = default;
    virtual bool LoadBios(QString biosFilePath) = 0;
    virtual bool LoadRom(QString romFilePath) = 0;
    virtual void Exec() = 0;
    virtual bool HasError() = 0;
    virtual void GetScreenSize(int& width, int& height) = 0;
    virtual void SetScreenBuffer(quint32* buffer, QMutex* bufferMutex) = 0;
};

#endif //IEMULATORCORE_H
