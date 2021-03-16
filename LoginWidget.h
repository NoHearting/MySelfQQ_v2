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
#include <functional>
#include <QScopedPointer>

#include "item_widgets/ComboBoxItemWidget.h"
#include "feature_widgets/SystemTray.h"
#include "feature_widgets/ToolTipWidget.h"
#include "main/Frameless.h"
#include "main/Data.h"

namespace Ui
{
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();


    /// @brief 关闭窗口
    void closeWindow();

private:
    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();

    /// @brief 初始化信号和槽
    void initSignalsAndSlots();

    /// @brief 初始化成员堆对象
    void initObjects();
    /**
     * @brief 释放成员对象数据
     */
    void deleteObjects();

private:
    Ui::LoginWidget *ui;

    QListWidget *comboBoxListWidget;        ///下拉组合框

    QPixmap head;       /// 头像


    // ------ 显示到托盘 -------------
    zsj::SystemTray * systemTray;


    // 提示窗口
    ToolTipWidget * toolTip;

    zsj::Frameless * frameless;


signals:
    void sigLoginSuccess(zsj::Data::ptr data);
private slots:


    /// @brief 最小化窗口
    void minWindow();

    /// @brief 根据下拉框选择的值设置账号和密码
    ///
    /// @param[in] head 头像
    /// @param[in] accountNum 账号
    /// @param[in] password 密码
    void setAccountAndPassword(const QPixmap &head,
                               const QString &accountNum, const QString &password);


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
