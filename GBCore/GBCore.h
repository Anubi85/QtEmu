#pragma once

#include "IEmulatorCore.h"
#include "GBComponent.h"

extern "C" Q_DECL_EXPORT IEmulatorCore* GetCore();

class GBCore : public IEmulatorCore
{
private:
    GBBus* m_Bus;
    GBInterruptBus* m_InterruptBus;
    GBComponent* m_Components[COMPONENT_NUM];
    Error m_Error;
public:
    GBCore();
    ~GBCore() override;
    void Exec() override;
    bool HasError() override;
    void GetScreenSize(int& width, int& height) override;
    quint32* GetVideoFrame() override;
    quint32 GetAudioBufferSize() override;
    quint8 * GetAudioSamples() override;
    bool Initialize(QString biosFilePath, QString romFilePath) override;
};
