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
#include <map>
#include <list>


#include "main/Frameless.h"
#include "feature_widgets/SystemTray.h"
#include "main/Linkman.h"
#include "feature_widgets/WarnDialog.h"

namespace Ui
{
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    typedef std::map<QTreeWidgetItem *, std::list<QTreeWidgetItem *>> mapTreeItem;
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:

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


    /// @brief 删除联系人列表元素
    ///
    /// @param item 删除的项目
    void deleteTreeWidgetItem(QTreeWidgetItem *item,
                              std::map<QTreeWidgetItem *, std::list<QTreeWidgetItem *>> &data);

    // 设置菜单的显示。不同的位置显示的菜单不一样。
    /// @brief 好友列表点击菜单
    void showFriendMenu();

    /// @brief 消息列表点击好友菜单
    void showMessageListFriendMenu();

    /// @brief 好友分组点击菜单
    void showFriendSectionMenu();

    /// @brief 默认好友分组点击菜单
    void showDefaultFriendSectionMenu();

    /// @brief 群组列表点击群组
    void showGroupMenu();

    /// @brief 消息列表点击群组
    void showMessageListGroupMenu();

    /// @brief 群组列表点击群分组
    void showGroupSectionMenu();

    /// @brief 群组列表点击默认群分组
    void showDefaultGroupSectionMenu();

    /// @brief 添加好友菜单子菜单
    void addFriendSubMenu(QMenu &menu,
                          std::map<QTreeWidgetItem *, std::list<QTreeWidgetItem *>> &data);

    /// @brief 添加群组菜单子菜单
    void addGroupSubMenu(QMenu &menu,
                         std::map<QTreeWidgetItem *, std::list<QTreeWidgetItem *>> &data);

    /// @brief 添加子菜单
    void updateSubMenu(QMenu * menu,QTreeWidget * treeWidget,
                    std::map<QTreeWidgetItem *, std::list<QTreeWidgetItem *>> &data);


    /// @brief 切换页面，在更换TreeWidget的页面的时候
    /// @param[in] currentIndex 当前页面坐标
    /// @param[in] targetIndex 将要切换的页面的坐标
    void changePage(int currentIndex,int targetIndex);

private:
    Ui::MainWidget *ui;

#ifdef Q_OS_LINUX
    QPoint offset;      /// 鼠标位移值
#endif


    /// 设置窗口可拉伸和移动
    zsj::Frameless *frameless = nullptr;

    /// 系统托盘
    zsj::SystemTray *systemTray = nullptr;

    /// 提示消息框
    WarnDialog *friendDialog = nullptr;
    WarnDialog *groupDialog = nullptr;

    // --------- 菜单 -----------
    QMenu *userMenu = nullptr;        /// 用户菜单

    QMenu *moveSubMenuFriend = nullptr;           /// “移动用户至（好友列表)”子菜单
    QMenu * moveSubMenuGroup = nullptr;           /// “移动群组至（群组列表）子菜单”


    QMenu *sectionMenu = nullptr;     /// 分组菜单
    QMenu *groupMenu = nullptr;       /// 群组菜单
    QMenu *groupSectionMenu = nullptr;    /// 群分组菜单

    // ------------ Global Data ------------
    // 当前类的全局数据，一个方法修改之后另一个方法会使用
    /// 当弹出菜单时，保存触发菜单的item
    QTreeWidgetItem *itemUser = nullptr;
    QTreeWidgetItem *itemGroup = nullptr;

    /// 当弹出菜单时，保存触发菜单的item
    QListWidgetItem *itemMessage = nullptr;

    /// 是否点击消息列表
    bool isMsgList;


    // --------- 数据 --------------
//    QMap<QString,QTreeWidgetItem*> rootNodeFriend;
//    QMap<QTreeWidgetItem*,QList<QTreeWidgetItem*>> childNodeFriend;
    mapTreeItem dataFriend;
    mapTreeItem dataGroup;

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

public slots:
    /// @brief 好友管理
    void friendManager() {}

    /// @brief 消息记录
    void messageRecord() {}

    /// @brief 移动联系人和群组
    void moveItem(QAction * action);

    // ========= userMenu槽函数 ==============
    /// @brief 发送即时消息
    void sendMessage() {}

    /// @brief 删除好友
    void deleteFriend();

    /// @brief 更新好友备注
    void updateRemark() {}

    /// @brief 移动好友
    void moveFriend() {}

    // ========== sectionMenu槽函数 =============
    /// @brief 添加分组
    void addSection() {}

    /// @brief 重命名分组
    void renameSection() {}

    /// @brief 删除分组
    void deleteFriendSection();

    // ========== groupMenu槽函数 =================
    /// @brief 发送群消息
    void sendGroupMessage() {}

    /// @brief 修改群备注
    void updateGroupRemark() {}

    /// @brief 移动群聊
    void moveGroupTo() {}


    // ============= groupSectionMenu =============
    /// @brief 查找添加群
    void findAndAddGroup() {}

    /// @brief 创建一个群
    void createGroup() {}

    /// @brief 添加群分组
    void addGroupSection() {}

    /// @brief 重命名群分组
    void renameGroupSection() {}

    /// @brief 删除群分组
    void deleteGroupSection();

    // ============= list**Menu ==============
    /// @brief 从会话列表移除
    void deleteItemFromMessageList();

};

#endif // MAINWIDGET_H
