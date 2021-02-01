/**
  * @brief 系统托盘类
  *     封装系统托盘，该系统托盘含有默认的菜单和图标。可以更改托盘图标和菜单
  * @author zsj
  * @date 2020年12月23日20:24:54
  */
#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H


#include <QObject>
#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

namespace zsj{

class SystemTray : public QObject
{
    Q_OBJECT
public:
    explicit SystemTray(QObject *parent = 0);
    SystemTray(QMenu * trayMenu,QPixmap * trayIcon,QObject *parent = 0);
    ~SystemTray();

    /// @brief 设置系统托盘菜单
    /// @param[in] value 菜单
    void setSystemTrayMenu(QMenu *value);

    /// @brief 设置系统托盘图标
    /// @param[in] value 图标
    void setSystemTrayIcon(QPixmap *value);

    /// @brief 显示系统托盘
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

    void openWindow(QSystemTrayIcon::ActivationReason reason);
};

}

#endif // SYSTEMTRAY_H
