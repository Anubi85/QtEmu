#ifndef GBCORE_H
#define GBCORE_H

#include "IEmulatorCore.h"
#include "GBComponent.h"
#include "GBUtils.h"

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
    void Exec() override;
    bool HasError() override;
    void GetScreenSize(int& width, int& height) override;
    quint32* GetFrame() override;
    bool Initialize(QString biosFilePath, QString romFilePath) override;
};

#endif // GBCORE_H
