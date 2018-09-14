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
    GBComponent* m_Components[*Component::TOTAL];
    Error m_Error;
public:
    GBCore();
    ~GBCore() override;
    bool LoadBios(QString biosFilePath) override;
    void Exec() override;
    bool HasError() override;
};

#endif // GBCORE_H
