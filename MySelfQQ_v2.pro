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
    MyComboBox.cpp \
    SystemTray.cpp \
    ToolTipWidget.cpp \
    MainWidget.cpp \
    LinkmanItemWidget.cpp \
    LinkmanGroupWidget.cpp

HEADERS  += LoginWidget.h \
    Frameless.h \
    ReadQStyleSheet.h \
    Util.h \
    Log.h \
    Test.h \
    HeadShadowWidget.h \
    ComboBoxItemWidget.h \
    MyComboBox.h \
    SystemTray.h \
    ToolTipWidget.h \
    MainWidget.h \
    LinkmanItemWidget.h \
    LinkmanGroupWidget.h

FORMS    += LoginWidget.ui \
    ComboBoxItemWidget.ui \
    ToolTipWidget.ui \
    MainWidget.ui \
    LinkmanItemWidget.ui \
    LinkmanGroupWidget.ui

RESOURCES += \
    qss.qrc \
    res.qrc

RC_ICONS = logo.ico
