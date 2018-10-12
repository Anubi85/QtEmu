#ifndef GBCPUSTATE_ERROR_H
#define GBCPUSTATE_ERROR_H

#include <QtGlobal>
#include <QString>
#include "IGBCpuState.h"

class GBCpuState_Error : public IGBCpuState
{
private:
    QString m_LastErrorDescription;
public:
    GBCpuState_Error(GBCpu* context, const QString errorDescription);
    void Update(GBBus* bus) override;
    CpuState GetStateID() override { return CpuState::Error; }
};

#endif // GBCPUSTATE_ERROR_H
