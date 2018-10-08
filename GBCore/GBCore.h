#ifndef GBCORE_H
#define GBCORE_H

#include "IEmulatorCore.h"
#include "GBComponent.h"
#include "GBUtils.h"

#define SCREEN_WIDTH  160
#define SCREEN_HEIGHT 144

extern "C" Q_DECL_EXPORT IEmulatorCore* GetCore();

class GBCore : public IEmulatorCore
{
private:
    GBBus* m_Bus;
    GBComponent* m_Components[*Component::Total];
    Error m_Error;
public:
    GBCore();
    ~GBCore() override;
    bool LoadBios(QString biosFilePath) override;
    bool LoadRom(QString romFilePath) override;
    void Exec() override;
    bool HasError() override;
    void GetScreenSize(int& width, int& height) override;
    void SetScreenBuffer(quint32* buffer, QMutex* bufferMutex) override;
};

#endif // GBCORE_H
