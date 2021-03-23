#-------------------------------------------------
#
# Project created by QtCreator 2020-12-10T15:32:24
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySelfQQ_v2
TEMPLATE = app

VERSION = 1.0.0.0
QMAKE_TAGGET_PRODUCT = MQ

SOURCES += main.cpp \
    ChatWidget.cpp \
    LoginWidget.cpp \
    MainWidget.cpp \
    customer_widgets/MyComboBox.cpp \
    customer_widgets/MyListWidget.cpp \
    customer_widgets/MySplitter.cpp \
    customer_widgets/MyTextEdit.cpp \
    customer_widgets/MyToolButton.cpp \
    customer_widgets/MyTreeWidget.cpp \
    feature_widgets/AnimationStackedWidget.cpp \
    feature_widgets/CacheWidget.cpp \
    feature_widgets/FloatScrollBar.cpp \
    feature_widgets/HeadShadowWidget.cpp \
    feature_widgets/SystemTray.cpp \
    feature_widgets/ToolTipWidget.cpp \
    feature_widgets/WarnDialog.cpp \
    item_widgets/ChatMessageItem.cpp \
    item_widgets/ChatMessageItemObject.cpp \
    item_widgets/ChatObjectItem.cpp \
    item_widgets/ComboBoxItemWidget.cpp \
    item_widgets/MessageItemWidget.cpp \
    main/ChatBubble.cpp \
    main/ChatMessageData.cpp \
    main/Data.cpp \
    main/Frameless.cpp \
    main/GroupData.cpp \
    main/Log.cpp \
    main/ReadQStyleSheet.cpp \
    main/StaticIniator.cpp \
    main/UserData.cpp \
    test/Test.cpp \
    utils/Util.cpp \
    screen_shot/Amplifier.cpp \
    screen_shot/CommonHelper.cpp \
    screen_shot/ScreenShot.cpp \
    feature_widgets/EmojiWidget.cpp \
    feature_widgets/EmojiTableWidget.cpp \
    main/EmojiInfo.cpp \
    main/StringUserData.cpp \
    feature_widgets/EmojiHotWidget.cpp \
    main/CurrentWindow.cpp \
    item_widgets/ChatMessageImageItemObject.cpp \
    main/ChatMessageRecord.cpp \
    test/TestWidget.cpp \
    item_widgets/ChatMessageFileItemObject.cpp \
    customer_widgets/MyPushButton.cpp \
    item_widgets/LinkmanSection.cpp \
    item_widgets/LinkmanUserItem.cpp \
    item_widgets/LinkmanGroupItem.cpp \
    item_widgets/LinkmanItem.cpp \
    main/ApplicationInfo.cpp \
    dao/LoginInfoDao.cpp \
    database/DataBase.cpp \
    database/SQLiteDataBase.cpp \
    main/LoginInfo.cpp \
    feature_widgets/PopupWidget.cpp



HEADERS  += ChatWidget.h \
    LoginWidget.h \
    MainWidget.h \
    customer_widgets/MyComboBox.h \
    customer_widgets/MyListWidget.h \
    customer_widgets/MySplitter.h \
    customer_widgets/MyTextEdit.h \
    customer_widgets/MyToolButton.h \
    customer_widgets/MyTreeWidget.h \
    feature_widgets/AnimationStackedWidget.h \
    feature_widgets/CacheWidget.h \
    feature_widgets/FloatScrollBar.h \
    feature_widgets/HeadShadowWidget.h \
    feature_widgets/SystemTray.h \
    feature_widgets/ToolTipWidget.h \
    feature_widgets/WarnDialog.h \
    item_widgets/ChatMessageItem.h \
    item_widgets/ChatMessageItemObject.h \
    item_widgets/ChatObjectItem.h \
    item_widgets/ComboBoxItemWidget.h \
    item_widgets/MessageItemWidget.h \
    main/ChatBubble.h \
    main/ChatMessageData.h \
    main/Data.h \
    main/Frameless.h \
    main/GroupData.h \
    main/Linkman.h \
    main/Log.h \
    main/NonCopyable.h \
    main/ReadQStyleSheet.h \
    main/StaticIniator.h \
    main/UserData.h \
    test/Test.h \
    utils/Global.h \
    utils/Util.h \
    screen_shot/CommonHelper.h \
    screen_shot/ScreenShot.h \
    screen_shot/Amplifier.h \
    feature_widgets/EmojiWidget.h \
    feature_widgets/EmojiTableWidget.h \
    main/EmojiInfo.h \
    main/StringUserData.h \
    feature_widgets/EmojiHotWidget.h \
    item_widgets/ChatMessageImageItemObject.h \
    main/ChatMessageRecord.h \
    test/TestWidget.h \
    item_widgets/ChatMessageFileItemObject.h \
    customer_widgets/MyPushButton.h \
    item_widgets/LinkmanSection.h \
    item_widgets/LinkmanUserItem.h \
    item_widgets/LinkmanGroupItem.h \
    item_widgets/LinkmanItem.h \
    main/CurrentWindow.h \
    main/ApplicationInfo.h \
    dao/LoginInfoDao.h \
    database/DataBase.h \
    database/SQLiteDataBase.h \
    main/LoginInfo.h \
    feature_widgets/PopupWidget.h


FORMS    +=     LoginWidget.ui \
    ChatWidget.ui \
    MainWidget.ui \
    feature_widgets/ToolTipWidget.ui \
    feature_widgets/WarnDialog.ui \
    item_widgets/ComboBoxItemWidget.ui \
    item_widgets/ChatObjectItem.ui \
    item_widgets/ChatMessageItemObject.ui \
    item_widgets/MessageItemWidget.ui \
    feature_widgets/EmojiWidget.ui \
    feature_widgets/EmojiHotWidget.ui \
    item_widgets/ChatMessageImageItemObject.ui \
    test/TestWidget.ui \
    item_widgets/ChatMessageFileItemObject.ui \
    item_widgets/LinkmanSection.ui \
    item_widgets/LinkmanUserItem.ui \
    item_widgets/LinkmanGroupItem.ui \
    feature_widgets/PopupWidget.ui




RESOURCES += \
    qss.qrc \
    res.qrc

RC_ICONS = logo.ico

