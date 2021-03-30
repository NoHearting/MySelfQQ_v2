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
#include <QSharedPointer>


#include "main/Frameless.h"
#include "feature_widgets/SystemTray.h"
#include "main/Linkman.h"
#include "feature_widgets/WarnDialog.h"
#include "ChatWidget.h"

#include "main/Data.h"
#include "main/UserData.h"
#include "main/GroupData.h"
#include "service/web/MainWebService.h"

namespace Ui
{
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    typedef std::map<QTreeWidgetItem *, std::list<QTreeWidgetItem *>> mapTreeItem;
    MainWidget(zsj::Data::ptr data, QWidget *parent = 0);
    ~MainWidget();

protected:

private:
    /// @brief 初始化窗口资源和窗口布局
    void initResourceAndForm();

    /// @brief 初始化信号和槽
    void initSignalsAndSlots();

    /// @brief 初始化成员堆对象
    void initObjects();

    /**
     * @brief 删除成员对象
     */
    void deleteObjects();


    /// @brief 初始化联系人好友列表
    void initManlinkFriend();

    /// @brief 初始化联系人群聊列表
    void initManlinkGroup();

    /// @brief 初始化消息列表
    void initMessageList();


    /// @brief 初始化所有需要用到的菜单
    void initMenus();

    /**
     * @brief 初始化用户数据
     */
    void initSelfData();

    /**
     * @brief 初始化好友和群组数据
     */
    void initUserAndGroupData();

    /**
     * @brief 初始化用户分组数据
     * @param userSections
     */
    void initUserSectionData(const QVector<zsj::SectionData> &userSections);

    /**
     * @brief 初始化群组分组数据
     * @param groupSection
     */
    void initGroupSectionData(const QVector<zsj::SectionData> &groupSections);

private:
    /// @brief 添加好友列表的根节点
    ///
    /// @param treeWidget 好友列表
    /// @param group 根节点
    QTreeWidgetItem *addTreeWidgetRootNode(QTreeWidget *treeWidget, const zsj::SectionData &sectionData);
    QTreeWidgetItem *addTreeWidgetRootNode(QTreeWidget *treeWidget, LinkmanSection *group);
    QTreeWidgetItem *addTreeWidgetRootNode(QTreeWidget *treeWidget, const QString &groupName, int active, int total);

    /// @brief 添加好友列表的子节点
    ///
    /// @param[in] 好友列表
    /// @param[in] 根节点
    /// @param[in] 子节点
    QTreeWidgetItem *addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode, LinkmanUserItem *item);
    QTreeWidgetItem *addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode,
                                            zsj::UserData::ptr userData);
    QTreeWidgetItem *addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode,
                                            zsj::GroupData::ptr groupData, const QString &date = QDateTime::currentDateTime().toString("yyyy-MM-dd"));




    void addMessageListItem(QListWidget *listWidget, zsj::Data::ptr data,
                            const QString &message,
                            const QDateTime &dateTime = QDateTime::currentDateTime());

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
    void updateSubMenu(QMenu *menu, QTreeWidget *treeWidget,
                       std::map<QTreeWidgetItem *, std::list<QTreeWidgetItem *>> &data);


    /// @brief 切换页面，在更换TreeWidget的页面的时候
    /// @param[in] currentIndex 当前页面坐标
    /// @param[in] targetIndex 将要切换的页面的坐标
    void changePage(int currentIndex, int targetIndex);

private:
    Ui::MainWidget *ui;



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
    QMenu *moveSubMenuGroup = nullptr;            /// “移动群组至（群组列表）子菜单”


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


    /// 聊天窗口
    ChatWidget *chatWidget;

    /// 自己的信息
    zsj::Data::ptr selfData;


    zsj::MainWebService mainWebService;
private slots:

    // ------- 最顶部功能按钮 ---------
    /// @brief 关闭窗口
    void slotCloseWindow();

    /// @brief 最小化窗口
    void slotMinWindow();

    /// @brief 界面管理器
    void slotInterfaceManager();


    /// @brief 切换到消息界面
    void slotSwitchToMessageWidget();

    /// @brief 切换到联系人界面
    void slotSwitchToLinkmanWidget();

    /// @brief 切换到空间界面
    void slotSwitchToSpaceWidget();


    /// @brief 子项目点击，
    /// 如果为根节点则不变化背景颜色,并且展开内容
    void slotTreeWidgetItemClick(QTreeWidgetItem *item, int );

    /// @brief 子项目收缩时
    /// 设置分组的图标
    void slotCollasped(QTreeWidgetItem *item);

    /// @brief 子项目展开时
    /// 设置分组的图标
    void slotExpanded(QTreeWidgetItem *item);

    // ------------- 菜单槽函数 -------------
    /// @brief 显示菜单
    void slotShowContextMenuFriend(const QPoint &);
    void slotShowContextMenuGroup(const QPoint &);
    void slotShowContextMenuMessage(const QPoint &);


    /**
     * @brief 打开聊天窗口
     * @param index 当前聊天对象在聊天列表中的坐标
     */
    void slotOpenChatWindow(const QModelIndex &index);          // 好友列表
    void slotOpenChatWindowGroup(const QModelIndex &index);     // 群组列表
    void slotOpenChatWindowMessage(const QModelIndex &index);   // 消息列表

    /**
     * @brief 根据信号改变消息列表item显示的日期和消息信息
     * @param data
     * @param fromId
     * @param toId
     * @param content
     * @param msgType
     */
    void slotChangeMessageListItemInfo(zsj::Data::ptr data, quint64 fromId, quint64 toId,
                                       const QString &content, zsj::global::MessageType msgType);
public slots:
    /// @brief 好友管理
    void slotFriendManager() {}

    /// @brief 消息记录
    void slotMessageRecord() {}

    /// @brief 移动联系人和群组
    void slotMoveItem(QAction *action);

    // ========= userMenu槽函数 ==============
    /// @brief 发送即时消息
    void slotSendMessage() {}

    /// @brief 删除好友
    void slotDeleteFriend();

    /// @brief 更新好友备注
    void slotUpdateRemark() {}

    /// @brief 移动好友
    void slotMoveFriend() {}

    // ========== sectionMenu槽函数 =============
    /// @brief 添加分组
    void slotAddSection() {}

    /// @brief 重命名分组
    void slotRenameSection() {}

    /// @brief 删除分组
    void slotDeleteFriendSection();

    // ========== groupMenu槽函数 =================
    /// @brief 发送群消息
    void slotSendGroupMessage() {}

    /// @brief 修改群备注
    void slotUpdateGroupRemark() {}

    /// @brief 移动群聊
    void slotMoveGroupTo() {}


    // ============= groupSectionMenu =============
    /// @brief 查找添加群
    void slotFindAndAddGroup() {}

    /// @brief 创建一个群
    void slotCreateGroup() {}

    /// @brief 添加群分组
    void slotAddGroupSection() {}

    /// @brief 重命名群分组
    void slotRenameGroupSection() {}

    /// @brief 删除群分组
    void slotDeleteGroupSection();

    // ============= list**Menu ==============
    /// @brief 从会话列表移除
    void slotDeleteItemFromMessageList();

};

#endif // MAINWIDGET_H
