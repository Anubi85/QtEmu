#-------------------------------------------------
#
# Project created by QtCreator 2018-09-12T09:00:55
#
#-------------------------------------------------

QT       -= gui

TARGET = GBCore
TEMPLATE = lib

DEFINES += GBCORE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG(debug, debug|release): DEFINES += DEBUG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

include(../QtEmu.pri)

SOURCES += \
    GBBus.cpp \
    GBComponent.cpp \
    GBBios.cpp \
    GBCpu.cpp \
    GBCpu_s.cpp \
    GBCpuState_Fetch.cpp \
    GBCore.cpp \
    GBCpuState_Decode.cpp \
    IGBCpuState.cpp \
    GBInstructionContext.cpp \
    GBCpuState_Execute.cpp \
    GBCpuState_InterruptCheck.cpp \
    GBCpuState_Error.cpp \
    GBAudio.cpp \
    GBVideo.cpp \
    GBCartridge.cpp \
    IGBCartridgeBehaviour.cpp \
    GBCartridgeBehaviour_RomOnly.cpp \
    GBInternalRam.cpp \
    IGBVideoState.cpp \
    GBVideoState_Scanline1.cpp \
    GBVideoState_Suspended.cpp \
    GBVideoState_Scanline2.cpp \
    GBVideoState_HBlank.cpp \
    GBVideoState_VBlank.cpp \
    IGBCpuStateContext.cpp \
    IGBVideoStateContext.cpp \
    GBVideo_s.cpp \
    GBRam.cpp \
    GBAudioChannel.cpp \
    IGBAudioModule.cpp \
    GBAudioModule_FrequencySweeper.cpp \
    GBAudioModule_SquareWaveGenerator_s.cpp \
    GBAudioModule_SquareWaveGenerator.cpp \
    GBAudioModule_LengthCounter.cpp \
    GBAudioModule_EnvelopeVolumeManager.cpp \
    GBAudioModule_Constant.cpp

HEADERS += \
    ../Includes/IEmulatorCore.h \
    GBBus.h \
    GBComponent.h \
    GBBios.h \
    GBCpu.h \
    IGBCpuState.h \
    GBCpuState_Fetch.h \
    GBCore.h \
    GBCpuState_Decode.h \
    GBInstructionContext.h \
    GBUtils.h \
    GBCpuState_Execute.h \
    GBInstruction.h \
    GBCpuState_InterruptCheck.h \
    GBCpuState_Error.h \
    GBAudio.h \
    GBVideo.h \
    GBCartridge.h \
    IGBCartridgeBehaviour.h \
    GBCartridgeBehaviour_RomOnly.h \
    GBInternalRam.h \
    IGBVideoState.h \
    GBVideoState_Scanline1.h \
    GBVideoState_Suspended.h \
    GBVideoState_Scanline2.h \
    GBVideoState_HBlank.h \
    GBVideoState_VBlank.h \
    IGBCpuStateContext.h \
    IGBVideoStateContext.h \
    GBRam.h \
    GBAudioChannel.h \
    GBAudioCommonDefs.h \
    IGBAudioModule.h \
    GBAudioModule_FrequencySweeper.h \
    GBAudioModule_SquareWaveGenerator.h \
    GBAudioModule_LengthCounter.h \
    GBAudioModule_EnvelopeVolumeManager.h \
    GBAudioModule_Constant.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
