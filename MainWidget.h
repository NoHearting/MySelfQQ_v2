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
#include <QListWidget>
#include <QMenu>


#include "Frameless.h"
#include "SystemTray.h"
#include "Linkman.h"

namespace Ui
{
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


    /// @brief 初始化所有需要用到的菜单
    void initMenus();


private:
    /// @brief 添加好友列表的根节点
    ///
    /// @param treeWidget 好友列表
    /// @param group 根节点
    QTreeWidgetItem *addTreeWidgetRootNode(QTreeWidget *treeWidget, LinkmanGroupWidget *group);
    QTreeWidgetItem *addTreeWidgetRootNode(QTreeWidget *treeWidget, const QString &groupName, int active, int total);

    /// @brief 添加好友列表的子节点
    ///
    /// @param[in] 好友列表
    /// @param[in] 根节点
    /// @param[in] 子节点
    QTreeWidgetItem *addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode, LinkmanItemWidget *item);
    QTreeWidgetItem *addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode,
                                            zsj::UserData::ptr userData);
    QTreeWidgetItem *addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode,
                                            zsj::GroupData::ptr groupData, const QString &date);


    /// 设置头像
    void setHead(QPixmap &pixmap);
    void setHead(const QString &pixmapPath);

private:
    Ui::MainWidget *ui;


    /// 设置窗口可拉伸和移动
    zsj::Frameless *frameless;

    /// 系统托盘
    zsj::SystemTray *systemTray;

    // --------- 菜单 -----------
    QMenu *userMenu;        /// 用户菜单
    QMenu *sectionMenu;     /// 分组菜单
    QMenu *groupMenu;       /// 群组菜单
    QMenu *groupSectionMenu;    /// 群分组菜单

    QMenu * listUserMenu;   /// 消息列表弹出的用户菜单
    QMenu * listGroupMenu;  /// 消息列表弹出的群组菜单

    /// 当弹出菜单时，保存触发菜单的item
    QTreeWidgetItem * itemUser;
    QTreeWidgetItem * itemGroup;

    /// 当弹出菜单时，保存触发菜单的item
    QListWidgetItem * itemMessage;


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
    void treeWidgetItemClick(QTreeWidgetItem *item, int );

    /// @brief 子项目收缩时
    /// 设置分组的图标
    void collasped(QTreeWidgetItem *item);

    /// @brief 子项目展开时
    /// 设置分组的图标
    void expanded(QTreeWidgetItem *item);

    // ------------- 菜单槽函数 -------------
    /// @brief 显示菜单
    void showContextMenuFriend(const QPoint &);
    void showContextMenuGroup(const QPoint &);
    void showContextMenuMessage(const QPoint &);

    /// @brief 好友管理
    void friendManager() {}

    /// @brief 消息记录
    void messageRecord() {}

    // ========= userMenu槽函数 ==============
    /// @brief 发送即时消息
    void sendMessage() {}

    /// @brief 发送电子邮件
    void sendEmail() {}

    /// @brief 消息免打扰
    void messageAvoid() {}

    /// @brief 设置权限
    void setPrivilege() {}

    /// @brief 删除好友
    void deleteFriend() {}

    /// @brief 更新好友备注
    void updateRemark() {}

    /// @brief 移动好友
    void moveFriend() {}

    /// @brief 举报此用户
    void reportFriend() {}

    /// @brief 会员快捷功能
    void vipFunction() {}

    /// @brief 进入空间
    void intoSpace() {}

    // ========== sectionMenu槽函数 =============
    /// @brief 刷新好友列表
    void updateFriendList() {}

    /// @brief 显示在线联系人
    void showOnlineFriends() {}

    /// @brief 隐身对该分组可见
    void hideToShowTheSection() {}

    /// @brief 在线对该分组隐身
    void onlineToHideTheSection() {}

    /// @brief 添加分组
    void addSection() {}

    /// @brief 重命名分组
    void renameSection() {}

    /// @brief 删除分组
    void deleteSection() {}

    // ========== groupMenu槽函数 =================
    /// @brief 发送群消息
    void sendGroupMessage() {}

    /// @brief 查看群资料
    void showGroupInfo() {}

    /// @brief 群消息设置
    void groupMessageSetting() {}

    /// @brief 修改群备注
    void updateGroupRemark() {}

    /// @brief 生成左面快捷方式
    void createDesktopShortcut() {}

    /// @brief 取消置顶
    void cancelIsTop() {}

    /// @brief 如何升级
    void howToUpgrade() {}

    /// @brief 退出该群
    void exitTheGroup() {}

    /// @brief 举报群聊
    void reportGroup() {}

    // ============= groupSectionMenu =============
    /// @brief 图标显示
    void iconShow() {}

    /// @brief 列表显示
    void listShow() {}

    /// @brief 访问MQ群官网
    void visitMQOfficialWebsite() {}

    /// @brief 查找添加群
    void findAndAddGroup() {}

    /// @brief 创建一个群
    void createGroup() {}

    /// @brief 添加群分组
    void addGroupSection() {}

    /// @brief 重命名群分组
    void renameGroupSection() {}

    /// @brief 删除群分组
    void deleteGroupSection() {}

    // ============= list**Menu ==============
    /// @brief 从会话列表移除
    void deleteItemFromMessageList(){}

};

#endif // MAINWIDGET_H
