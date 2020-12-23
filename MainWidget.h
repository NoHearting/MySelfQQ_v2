/**
  * @brief 主界面类
  *
  * @author zsj
  * @date 2020年12月23日20:12:48
  */
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTreeWidget>
#include <QMenu>


#include "Frameless.h"
#include "SystemTray.h"
#include "Linkman.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private:
    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();

    /// @brief 初始化信号和槽
    void initSignalsAndSlots();

    /// @brief 初始化成员堆对象
    void initObjects();


    /// @brief 初始化联系人好友列表
    void initManlinkFriend();

    /// @brief 初始化联系人群聊列表
    void initManlinkGroup();

    /// @brief 初始化消息列表
    void initMessageList();

    /// @brief 初始化用户菜单
    void initUserMenu();

private:
    /// @brief 添加好友列表的根节点
    ///
    /// @param treeWidget 好友列表
    /// @param group 根节点
    QTreeWidgetItem* addTreeWidgetRootNode(QTreeWidget * treeWidget,LinkmanGroupWidget * group);
    QTreeWidgetItem* addTreeWidgetRootNode(QTreeWidget * treeWidget,const QString & groupName,int active,int total);

    /// @brief 添加好友列表的子节点
    ///
    /// @param[in] 好友列表
    /// @param[in] 根节点
    /// @param[in] 子节点
    QTreeWidgetItem* addTreeWidgetChildNode(QTreeWidget * treeWidget,QTreeWidgetItem * rootNode,LinkmanItemWidget * item);
    QTreeWidgetItem* addTreeWidgetChildNode(QTreeWidget * treeWidget,QTreeWidgetItem * rootNode,
                                zsj::UserData::ptr userData);
    QTreeWidgetItem* addTreeWidgetChildNode(QTreeWidget * treeWidget,QTreeWidgetItem * rootNode,
                                zsj::GroupData::ptr groupData,const QString & date);


    /// 设置头像
    void setHead(QPixmap & pixmap);
    void setHead(const QString & pixmapPath);

private:
    Ui::MainWidget *ui;


    /// 设置窗口可拉伸和移动
    zsj::Frameless * frameless;

    /// 系统托盘
    zsj::SystemTray * systemTray;

    // --------- 菜单 -----------
    QMenu * userMenu;       /// 用户菜单


private slots:

    // ------- 最顶部功能按钮 ---------
    /// @brief 关闭窗口
    void closeWindow();

    /// @brief 最小化窗口
    void minWindow();

    /// @brief 界面管理器
    void interfaceManager();


    /// @brief 切换到消息界面
    void switchToMessageWidget();

    /// @brief 切换到联系人界面
    void switchToLinkmanWidget();

    /// @brief 切换到空间界面
    void switchToSpaceWidget();

    /// @brief 子项目点击，
    /// 如果为根节点则不变化背景颜色,并且展开内容
    void treeWidgetItemClick(QTreeWidgetItem * item, int );

    /// @brief 子项目收缩时
    /// 设置分组的图标
    void collasped(QTreeWidgetItem * item);

    /// @brief 子项目展开时
    /// 设置分组的图标
    void expanded(QTreeWidgetItem * item);

    // ------------- 菜单槽函数 -------------
    /// @brief 显示菜单
    void showContextMenuFriend(const QPoint &);
    void showContextMenuGroup(const QPoint &);

    /// @brief 发送即时消息
    void userMenuSendMessage();

    /// @brief 发送电子邮件
    void userMenuSendEmail();

    /// @brief 消息免打扰
    void userMenuMessageAvoid();

    /// @brief 消息记录
    void userMenuMessageRecord();

    /// @brief 设置权限
    void userMenuSetPrivilege();

    /// @brief 删除好友
    void userMenuDeleteFriend();

    /// @brief 更新好友备注
    void userMenuUpdateRemark();

    /// @brief 移动好友
    void userMenuMoveFriend();

    /// @brief 举报此用户
    void userMenuReportFriend();

    /// @brief 好友管理
    void userMenuFriendManager();

    /// @brief 会员快捷功能
    void userMenuVipFunction();

    /// @brief 进入空间
    void userMenuIntoSpace();



};

#endif // MAINWIDGET_H
