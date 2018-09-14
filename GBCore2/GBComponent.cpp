#include "GBComponent.h"

GBComponent::GBComponent()
{
    m_ErrorCode = Error::Ok;
}

void GBComponent::Reset()
{
    m_ErrorCode = Error::Ok;
}

GBComponent::~GBComponent() {}

QString GBComponent::GetErrorDescription(Error error)
{
    switch (error)
    {
    case Error::Ok:
        return "No Error";
    case Error::BIOS_FileNotFound:
        return  "Bios file not found n disk.";
    case Error::BIOS_FailToOpen:
        return "Fail to open the bios file.";
    case Error::BIOS_WrongFileSize:
        return "File size is not correct, expected size is 256 byte.";
    case Error::BIOS_WrongFileMD5:
        return "Bios MD5 checksum does not math.";
    default:
        return "Unrecognize error code";
    }
}