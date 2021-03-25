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
#include <QScopedPointer>

#include "item_widgets/ComboBoxItemWidget.h"
#include "feature_widgets/SystemTray.h"
#include "feature_widgets/ToolTipWidget.h"
#include "feature_widgets/PopupWidget.h"
#include "main/Frameless.h"
#include "main/Data.h"
#include "dao/LoginInfoDao.h"
#include  "service/web/LoginWebService.h"

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

    /**
     * @brief 加载并设置登录信息
     */
    void loadAndSetLoginInfo();

    /**
     * @brief 持久化登录数据
     */
    void persistenceLoginInfo(const zsj::LoginInfo & info);

private:
    Ui::LoginWidget *ui;

    QListWidget *comboBoxListWidget;        ///下拉组合框

    QPixmap head;       /// 头像


    // ------ 显示到托盘 -------------
    zsj::SystemTray * systemTray;


    // 提示窗口
    ToolTipWidget * toolTip;

    zsj::Frameless * frameless;

    /// 存储登录信息
    zsj::LoginInfoDao * infoDao;

    /// 当前登录用户的信息
    QVector<zsj::LoginInfo> infos;


    /// 下拉框  账号输入框的下拉框
    PopupWidget * popupWidget;

    /// 进行http请求
    zsj::LoginWebService * loginService;

    /// 是否允许登录
    bool cancelLogin = false;
signals:
    /**
     * @brief 登录成功时发送信号
     * @param data 当前用户的数据
     */
    void sigLoginSuccess(zsj::Data::ptr data);
public slots:

    /// @brief 关闭窗口
    void slotCloseWindow();
private slots:


    /// @brief 最小化窗口
    void slotMinWindow();

    /// @brief 根据下拉框选择的值设置账号和密码
    ///
    /// @param[in] head 头像
    /// @param[in] accountNum 账号
    /// @param[in] password 密码
    void slotSetAccountAndPassword(zsj::LoginInfo::ptr info);


    /// @brief 显示下拉框
    void slotShowComboBoxPopus();

    /// @brief 登录
    void slotLogin();

    /// @brief 取消登录
    void slotCancelLogin();

    /// @brief 找回密码，打开一个网页，执行找回密码
    void slotFindPassword();



};

#endif // LOGINWIDGET_H
