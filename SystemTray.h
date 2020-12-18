#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H


#include <QObject>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

namespace Zsj{

class SystemTray : public QObject
{
    Q_OBJECT
public:
    explicit SystemTray(QObject *parent = 0);
    SystemTray(QMenu * trayMenu,QPixmap * trayIcon,QObject *parent = 0);
    ~SystemTray();


    void setSystemTrayMenu(QMenu *value);

    void setSystemTrayIcon(QPixmap *value);

    void showSystemTray();
private:
    QSystemTrayIcon * tray;     //系统托盘
    QMenu * systemTrayMenu;     //系统托盘菜单
    QPixmap * systemTrayIcon;   //系统托盘图标

    QAction * defaultOpen;      //默认打开
    QAction * defaultQuit;      //默认退出
signals:
    /// @brief 默认点击系统托盘打开按钮时发送此信号
    void sigDefaultOpen();

    /// @brief 默认点击系统托盘关闭按钮时发送此信号
    void sigDefaultQuit();

    /// @brief 单击托盘时发送信号
    void sigOpenWindow();
public slots:
    void defaultOpenClicked();
    void defaultQuitClicked();

    void openWindow();
};

}

#endif // SYSTEMTRAY_H
