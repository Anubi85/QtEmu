#ifndef GBCORE_H
#define GBCORE_H

#include "IEmulatorCore.h"
#include "GBMemory.h"
#include "GBCpu.h"

extern "C" Q_DECL_EXPORT IEmulatorCore* GetCore();

class GBCore : public IEmulatorCore
{
private:
    GBMemory* m_Memory;
    GBCpu* m_Cpu;
public:
    GBCore();
    ~GBCore() override;
    bool LoadBios(QString biosFilePath) override;
    void Exec() override;
    bool HasError() override;
};

#endif // GBCORE_H
