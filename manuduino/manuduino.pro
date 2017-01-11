#-------------------------------------------------
#
# Project created by QtCreator 2016-12-18T13:13:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = manuduino
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pos.cpp \
    texteditor.cpp \
    entity.cpp \
    arrow.cpp \
    emptyentity.cpp \
    boardgrid.cpp \
    ServerConfigurationDialog.cpp \
    ManuduinoCompiler.cpp \
    RemoteManager.cpp

HEADERS  += mainwindow.h \
    base.h \
    const.h \
    pos.h \
    texteditor.h \
    entity.h \
    arrow.h \
    emptyentity.h \
    boardgrid.h \
    operation.h \
    ServerConfigurationDialog.h \
    ManuduinoCompiler.h \
    RemoteManager.h

FORMS    += mainwindow.ui \
    ServerConfigurationDialog.ui

RESOURCES += \
    image/image.qrc
