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

CONFIG += c++17

include(../QtEmu.pri)

INCLUDEPATH += \
    GBBios \
    GBCartridge \
    GBGpu \
    GBApu \
    GBCpu \
    GBGpu \
    GBRam \
    GBInterrupt \
    GBUtility

SOURCES += \
    GBBus.cpp \
    GBComponent.cpp \
    GBCore.cpp \
    GBBios/GBBios.cpp \
    GBCartridge/GBCartridge.cpp \
    GBCartridge/IGBCartridgeBehaviour.cpp \
    GBCartridge/GBCartridgeBehaviour_RomOnly.cpp \
    GBInterrupt/GBInterrupt.cpp \
    GBRam/GBRam.cpp \
    GBRam/GBInternalRam.cpp \
    GBApu/GBApu.cpp \
    GBApu/GBApu_ChannelBase.cpp \
    GBApu/GBApu_FrameSequencer.cpp \
    GBApu/GBApu_FrequencySweepModule.cpp \
    GBApu/GBApu_LengthCounterModule.cpp \
    GBApu/GBApu_LfsrModule.cpp \
    GBApu/GBApu_Mixer.cpp \
    GBApu/GBApu_NoiseChannel.cpp \
    GBApu/GBApu_RamModule.cpp \
    GBApu/GBApu_SquareChannel.cpp \
    GBApu/GBApu_SquareWaveModule.cpp \
    GBApu/GBApu_SquareWaveModule_s.cpp \
    GBApu/GBApu_SweepSquareChannel.cpp \
    GBApu/GBApu_VolumeEnvelopeModule.cpp \
    GBApu/GBApu_WaveChannel.cpp \
    GBGpu/GBGpu.cpp \
    GBGpu/GBGpu_s.cpp \
    GBGpu/IGBGpuState.cpp \
    GBGpu/GBGpuState_Scanline1.cpp \
    GBGpu/GBGpuState_Scanline2.cpp \
    GBGpu/GBGpuState_Suspended.cpp \
    GBGpu/GBGpuState_HBlank.cpp \
    GBGpu/GBGpuState_VBlank.cpp \
    GBCpu/IGBCpuState.cpp \
    GBCpu/GBCpu.cpp \
    GBCpu/GBCpu_s.cpp \
    GBCpu/GBCpuState_Fetch.cpp \
    GBCpu/GBCpuState_Decode.cpp \
    GBCpu/GBInstructionContext.cpp \
    GBCpu/GBCpuState_Execute.cpp \
    GBCpu/GBCpuState_InterruptCheck.cpp \

HEADERS += \
    ../Includes/IEmulatorCore.h \
    GBBus.h \
    GBComponent.h \
    GBCore.h \
    GBBios/GBBios.h \
    GBCartridge/GBCartridge.h \
    GBCartridge/IGBCartridgeBehaviour.h \
    GBCartridge/GBCartridgeBehaviour_RomOnly.h \
    GBInterrupt/GBInterrupt.h \
    GBMemoryMap.h \
    GBRam/GBRam.h \
    GBRam/GBInternalRam.h \
    GBUtility/GBCounter.h \
    GBUtility/GBUtils.h \
    GBApu/GBApu.h \
    GBApu/GBApu_CommonDefs.h \
    GBApu/GBApu_ChannelBase.h \
    GBApu/GBApu_ChannelModuleBase.h \
    GBApu/GBApu_Dac.h \
    GBApu/GBApu_FrameSequencer.h \
    GBApu/GBApu_FrequencySweepModule.h \
    GBApu/GBApu_LengthCounterModule.h \
    GBApu/GBApu_LfsrModule.h \
    GBApu/GBApu_Mixer.h \
    GBApu/GBApu_NoiseChannel.h \
    GBApu/GBApu_RamModule.h \
    GBApu/GBApu_SquareChannel.h \
    GBApu/GBApu_SquareWaveModule.h \
    GBApu/GBApu_SweepSquareChannel.h \
    GBApu/GBApu_VolumeEnvelopeModule.h \
    GBApu/GBApu_WaveChannel.h \
    GBGpu/GBGpu.h \
    GBGpu/IGBGpuStateContext.h \
    GBGpu/IGBGpuState.h \
    GBGpu/GBGpuState_Scanline1.h \
    GBGpu/GBGpuState_Scanline2.h \
    GBGpu/GBGpuState_Suspended.h \
    GBGpu/GBGpuState_HBlank.h \
    GBGpu/GBGpuState_VBlank.h \
    GBCpu/IGBCpuStateContext.h \
    GBCpu/IGBCpuState.h \
    GBCpu/GBCpu.h \
    GBCpu/GBCpuState_Fetch.h \
    GBCpu/GBCpuState_Decode.h \
    GBCpu/GBCpuState_Execute.h \
    GBCpu/GBCpuState_InterruptCheck.h \
    GBCpu/GBCpuState_Error.h \
    GBCpu/GBInstructionContext.h \
    GBCpu/GBInstruction.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES +=
