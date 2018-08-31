#ifndef GBCORE_H
#define GBCORE_H

#include "IEmulatorCore.h"
#include "GBMemory.h"

extern "C" Q_DECL_EXPORT IEmulatorCore* GetCore();

class GB : public IEmulatorCore
{
private:
    GBMemory* m_Memory;
public:
    GB();
    ~GB() override;
    bool LoadBios(QString biosFilePath) override;
    void Exec() override;
};

#endif // GBCORE_H
