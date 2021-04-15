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
include(GBBios/GBBios.pri)
include(GBCartridge/GBCartridge.pri)
include(GBAudio/GBAudio.pri)
include(GBVideo/GBVideo.pri)
include(GBApu/GBApu.pri)
include(GBCpu/GBCpu.pri)
include(GBGpu/GBGpu.pri)
include(GBRam/GBRam.pri)
include(GBUtility/GBUtility.pri)

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

HEADERS += \
    GBBus.h \
    GBComponent.h \
    GBCore.h \

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES +=
