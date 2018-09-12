#include "GBComponent.h"

GBComponent::GBComponent()
{
    m_ErrorCode = 0;
}

GBComponent::~GBComponent() {}

void GBComponent::Reset()
{
    m_ErrorCode = 0;
}
