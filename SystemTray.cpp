#include "SystemTray.h"

#include <QDebug>

namespace Zsj{

SystemTray::SystemTray(QObject *parent) : QObject(parent)
{
    //初始化系统托盘
    systemTrayIcon = new QPixmap(":/global/res/global/water-gray.png");

    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon(*systemTrayIcon));
    tray->setToolTip("MQ");
    connect(tray,&QSystemTrayIcon::activated,this,&SystemTray::openWindow);

    // 初始化系统托盘菜单项
    defaultOpen = new QAction("打开主界面",this);
    defaultQuit = new QAction("退出",this);
    connect(defaultOpen,&QAction::triggered,this,&SystemTray::defaultOpenClicked);
    connect(defaultQuit,&QAction::triggered,this,&SystemTray::defaultQuitClicked);

    systemTrayMenu = new QMenu();
    systemTrayMenu->addAction(defaultOpen);
    systemTrayMenu->addSeparator();
    systemTrayMenu->addAction(defaultQuit);
    tray->setContextMenu(systemTrayMenu);

    systemTrayMenu->setWindowFlags(systemTrayMenu->windowFlags() |  Qt::FramelessWindowHint);
    systemTrayMenu->setAttribute(Qt::WA_TranslucentBackground);
    // 给系统托盘菜单添加css
    systemTrayMenu->setStyleSheet("QMenu{background:rgba(255,255,255,0.7);"
                                  "border-radius:5px;"
                                  "height:80px;width:135px;}"
                                  "QMenu::item{"
                                  "height:30px;"
                                  "margin:5px 0px;"
                                  "padding:0px 10px;"
                                  "}"
                                  "QMenu::item:selected:enabled{"
                                  "background:rgb(238,238,238);}"
                                  "QMenu::separator{"
                                  "height:1px;"
                                  "color:gray;}");
}

SystemTray::SystemTray(QMenu *trayMenu, QPixmap *trayIcon, QObject *parent) :QObject(parent)
{
    if(nullptr == trayIcon || trayIcon->isNull()){
        qWarning() << "system tray icon(QPixmap) is null!";
        systemTrayIcon = new QPixmap(":/global/res/global/water-gray.png");
    }
    else{
        systemTrayIcon = trayIcon;
    }

    tray = new QSystemTrayIcon(this);
    tray->setIcon(QIcon(*systemTrayIcon));
    tray->setToolTip("MQ");

    if(nullptr == trayMenu || trayMenu->isEmpty()){
        qWarning() << "system tray menu(QMenu) is null!";
        systemTrayMenu = new QMenu();
        systemTrayMenu->addAction(defaultOpen);
        systemTrayMenu->addSeparator();
        systemTrayMenu->addAction(defaultQuit);
    }
    else{
        systemTrayMenu = trayMenu;
    }

    tray->setContextMenu(systemTrayMenu);
}

SystemTray::~SystemTray()
{
    if(systemTrayIcon){
        delete systemTrayIcon;
    }
    if(systemTrayMenu){
        delete systemTrayMenu;
    }
}

void SystemTray::setSystemTrayMenu(QMenu *value)
{
    if(nullptr != value && !value->isEmpty()){
        delete systemTrayMenu;
        systemTrayMenu = value;
        tray->setContextMenu(systemTrayMenu);
    }
    else{
        qWarning() << "system tray menu is null,not to set!";
    }
}

void SystemTray::setSystemTrayIcon(QPixmap *value)
{
    if(nullptr != value && !value->isNull()){
        delete systemTrayIcon;
        systemTrayIcon = value;
        tray->setIcon(QIcon(*systemTrayIcon));      //这里的QPixmap不应该设置父对象
    }
    else{
        qWarning() << "system tray icon is null,not to set!";
    }
}

void SystemTray::showSystemTray()
{
    tray->show();
}

void SystemTray::defaultOpenClicked()
{
    emit sigDefaultOpen();
}

void SystemTray::defaultQuitClicked()
{
    emit sigDefaultQuit();
}

void SystemTray::openWindow()
{
    emit sigOpenWindow();
}

}
