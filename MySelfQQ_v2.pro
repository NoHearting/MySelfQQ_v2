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
    Log.cpp \
    Test.cpp \
    HeadShadowWidget.cpp \
    ComboBoxItemWidget.cpp \
    MyComboBox.cpp

HEADERS  += LoginWidget.h \
    Frameless.h \
    ReadQStyleSheet.h \
    Util.h \
    Log.h \
    Test.h \
    HeadShadowWidget.h \
    ComboBoxItemWidget.h \
    MyComboBox.h

FORMS    += LoginWidget.ui \
    ComboBoxItemWidget.ui

RESOURCES += \
    qss.qrc \
    res.qrc

RC_ICONS = logo.ico
