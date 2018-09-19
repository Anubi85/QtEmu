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
    case Error::BUS_ReadRequestNotServed:
        return "Unhandled Read request on bus.";
    case Error::BUS_WriteRequestNotServed:
        return "Unhandled write request on bus.";
    case Error::CPU_OpCodeNotImplemented:
        return "Requested the execution of an unimplemented op code.";
    case Error::CPU_UnespectedOpCodeStep:
        return "Unespected execution step for the current op code.";
    case Error::AUDIO_ReadFromNotValidRegister:
        return "Attempt to read from an invalid audio register.";
    case Error::AUDIO_WriteToNotValidRegister:
        return "Attempt to write to an invalid audio register.";
    default:
        return "Unrecognize error code";
    }
}
