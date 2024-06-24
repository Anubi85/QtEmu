#include "GBComponent.h"

QString GBComponent::GetErrorDescription(Error error)
{
    switch (error)
    {
    case Error::Ok:
        return "No Error";
    case Error::BIOS_FileNotFound:
		return  "Bios file not found on disk.";
    case Error::BIOS_FailToOpen:
        return "Fail to open the bios file.";
    case Error::BIOS_WrongFileSize:
        return "File size is not correct, expected size is 256 byte.";
    case Error::BIOS_WrongFileMD5:
        return "Bios MD5 checksum does not math.";
	case Error::MAINBUS_ReadRequestNotServed:
		return "Unhandled Read request on main bus.";
	case Error::MAINBUS_WriteRequestNotServed:
		return "Unhandled write request on main bus.";
	case Error::DMABUS_ReadRequestNotServed:
		return "Unhandled Read request on DMA bus.";
	case Error::DMABUS_WriteRequestNotServed:
		return "Unhandled write request on DMA bus.";
    case Error::CPU_OpCodeNotImplemented:
        return "Requested the execution of an unimplemented op code.";
    case Error::CPU_UnespectedOpCodeStep:
        return "Unespected execution step for the current op code.";
    default:
        return "Unrecognize error code";
    }
}
