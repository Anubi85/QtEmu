#-------------------------------------------------
#
# Project created by QtCreator 2018-08-30T09:05:20
#
#-------------------------------------------------

QT       -= gui

TARGET = GBCore
TEMPLATE = lib

DEFINES += GBCore_LIBRARY

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

include(../QtGB.pri)

SOURCES += \
        GBCore.cpp \
    GBMemory.cpp \
    GBCpu.cpp \
    OpCode.cpp \
    GBCpu_s.cpp \
    GBHardware.cpp \
    GBComponent.cpp

HEADERS += \
        GBCore.h \
    ../Includes/IEmulatorCore.h \
    GBMemory.h \
    GBCpu.h \
    OpCode.h \
    GBHardware.h \
    GBComponent.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
