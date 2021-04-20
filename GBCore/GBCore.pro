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
    GBAudio \
    GBVideo \
    GBApu \
    GBCpu \
    GBGpu \
    GBRam \
    GBUtility

SOURCES += \
    GBBus.cpp \
    GBComponent.cpp \
    GBCore.cpp \
    GBBios/GBBios.cpp \
    GBAudio/GBAudioDac.cpp \                            #TODO: remove
    GBAudio/GBAudioMixer.cpp \                          #TODO: remove
    GBAudio/GBAudio.cpp \                               #TODO: remove
    GBAudio/GBAudioChannel.cpp \                        #TODO: remove
    GBAudio/IGBAudioModule.cpp \                        #TODO: remove
    GBAudio/GBAudioModule_FrequencySweeper.cpp \        #TODO: remove
    GBAudio/GBAudioModule_SquareWaveGenerator_s.cpp \   #TODO: remove
    GBAudio/GBAudioModule_SquareWaveGenerator.cpp \     #TODO: remove
    GBAudio/GBAudioModule_LengthCounter.cpp \           #TODO: remove
    GBAudio/GBAudioModule_EnvelopeVolumeManager.cpp \   #TODO: remove
    GBAudio/GBAudioModule_Constant.cpp \                #TODO: remove
    GBAudio/GBAudioModule_RamWaveGenerator.cpp \        #TODO: remove
    GBAudio/GBAudioModule_NoiseWaveGenerator.cpp \      #TODO: remove
    GBAudio/GBAudioModule_RamWaveGenerator_s.cpp \      #TODO: remove
    GBAudio/GBAudioModule_NoiseWaveGenerator_s.cpp \    #TODO: remove
    GBCartridge/GBCartridge.cpp \
    GBCartridge/IGBCartridgeBehaviour.cpp \
    GBCartridge/GBCartridgeBehaviour_RomOnly.cpp \
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
    GBVideo/GBVideo.cpp \                               #TODO: rename Video to Gpu
    GBVideo/IGBVideoState.cpp \                         #TODO: rename Video to Gpu
    GBVideo/GBVideoState_Scanline1.cpp \                #TODO: rename Video to Gpu
    GBVideo/GBVideoState_Suspended.cpp \                #TODO: rename Video to Gpu
    GBVideo/GBVideoState_Scanline2.cpp \                #TODO: rename Video to Gpu
    GBVideo/GBVideoState_HBlank.cpp \                   #TODO: rename Video to Gpu
    GBVideo/GBVideoState_VBlank.cpp \                   #TODO: rename Video to Gpu
    GBVideo/IGBVideoStateContext.cpp \                  #TODO: rename Video to Gpu
    GBVideo/GBVideo_s.cpp \                             #TODO: rename Video to Gpu
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
    GBAudio/GBAudioDac.h \                              #TODO: remove
    GBAudio/GBAudioMixer.h \                            #TODO: remove
    GBAudio/GBAudio.h \                                 #TODO: remove
    GBAudio/GBAudioChannel.h \                          #TODO: remove
    GBAudio/GBAudioCommonDefs.h \                       #TODO: remove
    GBAudio/IGBAudioModule.h \                          #TODO: remove
    GBAudio/GBAudioModule_FrequencySweeper.h \          #TODO: remove
    GBAudio/GBAudioModule_SquareWaveGenerator.h \       #TODO: remove
    GBAudio/GBAudioModule_LengthCounter.h \             #TODO: remove
    GBAudio/GBAudioModule_EnvelopeVolumeManager.h \     #TODO: remove
    GBAudio/GBAudioModule_Constant.h \                  #TODO: remove
    GBAudio/GBAudioModule_RamWaveGenerator.h \          #TODO: remove
    GBAudio/GBAudioModule_NoiseWaveGenerator.h \        #TODO: remove
    GBCartridge/GBCartridge.h \
    GBCartridge/IGBCartridgeBehaviour.h \
    GBCartridge/GBCartridgeBehaviour_RomOnly.h \
    GBRam/GBRam.h \
    GBRam/GBInternalRam.h \
    GBUtility/GBCounter.h \
    GBUtility/GBUtils.h \
    GBApu/GBApu.h \
    GBApu/GBApuCommonDefs.h \
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
    GBVideo/GBVideo.h \                                 #TODO: rename Video to Gpu
    GBVideo/IGBVideoState.h \                           #TODO: rename Video to Gpu
    GBVideo/GBVideoState_Scanline1.h \                  #TODO: rename Video to Gpu
    GBVideo/GBVideoState_Suspended.h \                  #TODO: rename Video to Gpu
    GBVideo/GBVideoState_Scanline2.h \                  #TODO: rename Video to Gpu
    GBVideo/GBVideoState_HBlank.h \                     #TODO: rename Video to Gpu
    GBVideo/GBVideoState_VBlank.h \                     #TODO: rename Video to Gpu
    GBVideo/IGBVideoStateContext.h \                    #TODO: rename Video to Gpu
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
