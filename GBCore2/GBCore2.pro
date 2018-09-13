#-------------------------------------------------
#
# Project created by QtCreator 2018-09-12T09:00:55
#
#-------------------------------------------------

QT       -= gui

TARGET = GBCore2
TEMPLATE = lib

DEFINES += GBCORE2_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14

include(../QtGB.pri)

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
    GBCpuState_CBFetch.cpp \
    GBCpuState_Execute.cpp \
    GBCpuState_InterruptCheck.cpp

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
    GBCpuState_CBFetch.h \
    GBCpuState_Execute.h \
    GBInstruction.h \
    GBCpuState_InterruptCheck.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
