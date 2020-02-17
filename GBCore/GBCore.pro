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
    GBApu/GBApu.cpp \
    GBApu/GBApu_ChannelBase.cpp \
    GBApu/GBApu_FrameSequencer.cpp \
    GBApu/GBApu_FrequencySweepModule.cpp \
    GBApu/GBApu_LengthCounterModule.cpp \
    GBApu/GBApu_Mixer.cpp \
    GBApu/GBApu_SquareChannel.cpp \
    GBApu/GBApu_SquareWaveModule.cpp \
    GBApu/GBApu_SquareWaveModule_s.cpp \
    GBApu/GBApu_SweepSquareChannel.cpp \
    GBApu/GBApu_VolumeEnvelopeModule.cpp \
    GBAudioDac.cpp \
    GBAudioMixer.cpp \
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
    GBAudioModule_Constant.cpp \
    GBAudioModule_RamWaveGenerator.cpp \
    GBAudioModule_NoiseWaveGenerator.cpp \
    GBAudioModule_RamWaveGenerator_s.cpp \
    GBAudioModule_NoiseWaveGenerator_s.cpp

HEADERS += \
    ../Includes/IEmulatorCore.h \
    GBApu/GBApu.h \
    GBApu/GBApuCommonDefs.h \
    GBApu/GBApu_ChannelBase.h \
    GBApu/GBApu_ChannelModuleBase.h \
    GBApu/GBApu_Dac.h \
    GBApu/GBApu_FrameSequencer.h \
    GBApu/GBApu_FrequencySweepModule.h \
    GBApu/GBApu_LengthCounterModule.h \
    GBApu/GBApu_Mixer.h \
    GBApu/GBApu_SquareChannel.h \
    GBApu/GBApu_SquareWaveModule.h \
    GBApu/GBApu_SweepSquareChannel.h \
    GBApu/GBApu_VolumeEnvelopeModule.h \
    GBAudioDac.h \
    GBAudioMixer.h \
    GBBus.h \
    GBComponent.h \
    GBBios.h \
    GBCpu.h \
    GBUtility/GBCounter.h \
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
    GBAudioModule_Constant.h \
    GBAudioModule_RamWaveGenerator.h \
    GBAudioModule_NoiseWaveGenerator.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES +=
