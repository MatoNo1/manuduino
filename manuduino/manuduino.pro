#-------------------------------------------------
#
# Project created by QtCreator 2016-12-18T13:13:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
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
    RemoteManager.cpp \
    selectordialog.cpp \
    operationentity.cpp \
    boolcontrollerdialog.cpp \
    intcontrollerdialog.cpp \
    comparatordialog.cpp \
    outputdialog.cpp \
    bitsetterdialog.cpp \
    compiler.cpp

HEADERS  += mainwindow.h \
    base.h \
    const.h \
    pos.h \
    texteditor.h \
    entity.h \
    arrow.h \
    emptyentity.h \
    boardgrid.h \
    ServerConfigurationDialog.h \
    RemoteManager.h \
    ServerConfigurationDialog.h \
    selectordialog.h \
    operationentity.h \
    boolcontrollerdialog.h \
    intcontrollerdialog.h \
    comparatordialog.h \
    outputdialog.h \
    bitsetterdialog.h \
    compiler.h

FORMS    += mainwindow.ui \
    ServerConfigurationDialog.ui

RESOURCES += \
    image/image.qrc
