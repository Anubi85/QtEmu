#include "IGBCartridgeBehaviour.h"

IGBCartridgeBehaviour::IGBCartridgeBehaviour(quint8* data, quint32 size)
{
    m_Data = new quint8[size];
    memcpy(m_Data, data, size);
    m_DataSize = size;
}

IGBCartridgeBehaviour::~IGBCartridgeBehaviour()
{
    delete [] m_Data;
}
