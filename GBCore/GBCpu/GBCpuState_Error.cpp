#include "GBCpuState_Error.h"
#include "GBBus.h"

GBCpuState_Error::GBCpuState_Error(IGBCpuStateContext* context, const QString errorDescription) :
    IGBCpuState (context)
{
    m_LastErrorDescription = errorDescription;
#ifdef DEBUG
    qDebug(errorDescription.toUtf8());
#endif
}

void GBCpuState_Error::Update(GBBus* bus)
{
    //never exit the state and delete any pending request
    bus->Clear();
}
