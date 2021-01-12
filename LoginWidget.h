/**
  * @brief 登录界面类
  *
  * @author zsj
  * @date 2020年12月23日20:12:07
  */
#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QListWidget>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QAction>

#include "ComboBoxItemWidget.h"
#include "SystemTray.h"
#include "ToolTipWidget.h"
#include "Frameless.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

protected:
//    //无边框窗口需要重写鼠标点击和移动时间
//    /// @brief 重写mouseMoveEvent函数
//    ///
//    ///     用户点击有可能点击登录页面之上的小部件然后拖动
//    ///会出现抖动，此函数解决此问题
//    void mouseMoveEvent(QMouseEvent *);

//    /// @brief 重写mousePressEvent函数
//    ///
//    ///  鼠标按下事件，按下就获取当前鼠标坐标并计算出当前坐标和窗口左上角的差值
//    void mousePressEvent(QMouseEvent *);

//    /// @brief 重写mouseReleaseEvent函数
//    void mouseReleaseEvent(QMouseEvent *);




private:
    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();

    /// @brief 初始化信号和槽
    void initSignalsAndSlots();

    /// @brief 初始化成员堆对象
    void initObjects();

private:
    Ui::LoginWidget *ui;

    QPoint offset;       ///鼠标点击位置和窗口左上角的差值

    QListWidget * comboBoxListWidget;       ///下拉组合框

    QPixmap head;       /// 头像


    // ------ 显示到托盘 -------------
    zsj::SystemTray * systemTray;


    // 提示窗口
    ToolTipWidget * toolTip;

    zsj::Frameless * frameless = nullptr;


private slots:
    /// @brief 关闭窗口
    void closeWindow();

    /// @brief 最小化窗口
    void minWindow();

    /// @brief 根据下拉框选择的值设置账号和密码
    ///
    /// @param[in] head 头像
    /// @param[in] accountNum 账号
    /// @param[in] password 密码
    void setAccountAndPassword(const QPixmap & head,
                               const QString & accountNum,const QString & password);


    /// @brief 显示下拉框
    void showComboBoxPopus();

    /// @brief 登录
    void login();

    /// @brief 取消登录
    void cancelLogin();

    /// @brief 找回密码，打开一个网页，执行找回密码
    void findPassword();
};

#endif // LOGINWIDGET_H
