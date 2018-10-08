#ifndef GBCPUSTATE_ERROR_H
#define GBCPUSTATE_ERROR_H

#include <QtCore>
#include "IGBCpuState.h"

class GBCpuState_Error : public IGBCpuState
{
private:
    QString m_LastErrorDescription;
public:
    GBCpuState_Error(GBCpu* context, const QString errorDescription);
    void Update(GBBus* bus) override;
    State GetStateID() override { return State::Error; }
};

#endif // GBCPUSTATE_ERROR_H
