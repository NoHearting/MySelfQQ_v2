#-------------------------------------------------
#
# Project created by QtCreator 2020-12-10T15:32:24
#
#-------------------------------------------------

QT       += core gui
CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySelfQQ_v2
TEMPLATE = app


SOURCES += main.cpp\
        LoginWidget.cpp \
    Frameless.cpp \
    ReadQStyleSheet.cpp \
    Util.cpp \
    Log.cpp

HEADERS  += LoginWidget.h \
    Frameless.h \
    ReadQStyleSheet.h \
    Util.h \
    Log.h

FORMS    += LoginWidget.ui

RESOURCES += \
    qss.qrc
