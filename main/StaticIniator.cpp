#include "main/StaticIniator.h"
#include "MainWidget.h"
#include "ChatWidget.h"
#include "utils/Util.h"
#include "main/ReadQStyleSheet.h"
#include "utils/Global.h"

#include <QMutex>
#include <QMutexLocker>
#include <QActionGroup>

namespace zsj {

QScopedPointer<StaticIniator> StaticIniator::staticIniator;

StaticIniator *StaticIniator::Instance()
{
    if(staticIniator.isNull()){
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if(staticIniator.isNull()){
            staticIniator.reset(new StaticIniator);
        }
    }
    return staticIniator.data();
}

void zsj::StaticIniator::initFirendMenu(QMenu *menu,QWidget * owner)
{
    /*
     * 菜单选项
     *
     * - 发送即时消息 *
     * - 标为未读   x
     * - 发送电子邮件
     *
     * - 查看资料
     * - 消息免打扰
     * - 分享他们的名片
     * - 消息记录 *
     *
     * - 取消置顶    x
     * - 设为置顶    x
     * - 从会话列表删除
     * - 设置权限
     * - 修改好友备注 *
     * - 移动联系人至 *
     * - 删除好友 *
     * - 举报此用户
     * - 好友管理 *
     *
     * - 会员快捷功能
     * - 进入MQ空间
     */

    MainWidget * ownerChild = dynamic_cast<MainWidget*>(owner);
    menu->setObjectName("userMenu");
    QIcon icon = QIcon(zsj::global::TransparentMenuIconPath);
    QAction * sendMessage = new QAction(icon, "发送即时消息",menu);
    QAction * sendEmail = new QAction(icon, "发送电子邮件",menu);
    QAction * showInfo = new QAction(icon, "查看资料",menu);
    QAction * messageAvoid = new QAction(icon, "消息免打扰",menu);
    QAction * shareCard = new QAction(icon, "分享他的名片",menu);
    QAction * messageRecord = new QAction(QIcon(":/main/res/main/message-record.png"), "消息记录",menu);
    QAction * removeFromList = new QAction(icon, "从会话列表中移除",menu);
    QAction * setPrivilege = new QAction(icon, "设置权限",menu);
    QAction * updateRemark = new QAction(QIcon(":/main/res/main/update-remark.png"), "修改好友备注",menu);
    QAction * moveFriend = new QAction(QIcon(":/main/res/main/move-friends.png"), "移动联系人至",menu);
    QAction * deleteFriend = new QAction(QIcon(":/main/res/main/delete-friend.png"), "删除好友",menu);
    QAction * reportFriend = new QAction(icon, "举报此用户",menu);
    QAction * vipFunction = new QAction(icon, "会员快捷功能",menu);
    QAction * intoSpace = new QAction(QIcon(":/main/res/main/space.png"), "进入MQ空间",menu);

    menu->addAction(sendMessage);
    menu->addAction(sendEmail);
    menu->addSeparator();
    menu->addAction(showInfo);
    menu->addAction(messageAvoid);
    menu->addAction(shareCard);
    menu->addAction(messageRecord);
    menu->addSeparator();
    menu->addAction(removeFromList);
    menu->addAction(setPrivilege);
    menu->addAction(updateRemark);
    menu->addAction(moveFriend);
    menu->addAction(deleteFriend);
    menu->addAction(reportFriend);
    menu->addSeparator();
    menu->addAction(vipFunction);
    menu->addAction(intoSpace);

    initMenusStyle(menu);

    connect(removeFromList,&QAction::triggered,ownerChild,&MainWidget::slotDeleteItemFromMessageList);
    connect(deleteFriend,&QAction::triggered,ownerChild,&MainWidget::slotDeleteFriend);
}

void StaticIniator::initFirendSectionMenu(QMenu *menu,QWidget * owner)
{
    MainWidget * ownerChild = dynamic_cast<MainWidget*>(owner);
    menu->setObjectName("sectionMenu");

    QIcon icon = QIcon(zsj::global::TransparentMenuIconPath);
    QAction * updateFriendList = new QAction(icon, "刷新好友列表",menu);
    QAction * showOnline = new QAction(icon, "显示在线联系人",menu);
    QAction * hideToShowTheSection = new QAction(icon, "隐身对该分组可见",menu);
    QAction * showOnlineFriends = new QAction(icon, "在线对该分组隐身",menu);
    QAction * addSection = new QAction(icon, "添加分组",menu);
    QAction * renameSection  = new QAction(icon, "重命名",menu);
    QAction * deleteFriendSection = new QAction(QIcon(":/main/res/main/delete-section.png"),"删除该组",menu);
    QAction * friendManager = new QAction(QIcon(":/main/res/main/friend-manager.png"),"好友管理器",menu);

    menu->addAction(updateFriendList);
    menu->addAction(showOnline);
    menu->addSeparator();
    menu->addAction(hideToShowTheSection);
    menu->addAction(showOnlineFriends);
    menu->addSeparator();
    menu->addAction(addSection);
    menu->addAction(renameSection);
    menu->addAction(deleteFriendSection);
    menu->addAction(friendManager);


    initMenusStyle(menu);

    connect(deleteFriendSection,&QAction::triggered,ownerChild,&MainWidget::slotDeleteFriendSection);
    connect(addSection,&QAction::triggered,ownerChild,&MainWidget::slotAddSection);
    connect(renameSection,&QAction::triggered,ownerChild,&MainWidget::slotRenameSection);
}

void StaticIniator::initGroupMenu(QMenu *menu,QWidget * owner)
{
    MainWidget * ownerChild = dynamic_cast<MainWidget*>(owner);
    menu->setObjectName("groupMenu");
    QIcon icon = QIcon(zsj::global::TransparentMenuIconPath);
    QAction * sendGroupMessage = new QAction(icon, "发送群消息",menu);
    QAction * showGroupInfo = new QAction(QIcon(":/main/res/main/group-data.png"),"查看群资料",menu);
    QAction * groupMessageSet = new QAction(icon, "群消息设置",menu);
    QAction * removeFromList = new QAction(icon, "从会话列表移除",menu);
    QAction * updateRemark = new QAction(QIcon(":/main/res/main/update-remark.png"),"修改群备注",menu);
    QAction * createShortcut = new QAction(icon, "生成桌面快捷方式",menu);
    QAction * moveGroup = new QAction(icon, "移动群至",menu);
    QAction * upgrade = new QAction(icon, "如何升级",menu);
    QAction * exitGroup = new QAction(icon, "退出该群",menu);
    QAction * reportGroup = new QAction(icon, "举报该群",menu);


    menu->addAction(sendGroupMessage);
    menu->addSeparator();
    menu->addAction(showGroupInfo);
    menu->addAction(groupMessageSet);
    menu->addAction(updateRemark);
    menu->addSeparator();
    menu->addAction(removeFromList);
    menu->addAction(createShortcut);
    menu->addAction(moveGroup);
    menu->addSeparator();
    menu->addAction(upgrade);
    menu->addAction(exitGroup);
    menu->addAction(reportGroup);

    initMenusStyle(menu);


    connect(sendGroupMessage,&QAction::triggered,ownerChild,&MainWidget::slotSendGroupMessage);
    connect(updateRemark,&QAction::triggered,ownerChild,&MainWidget::slotUpdateGroupRemark);
    connect(moveGroup,&QAction::triggered,ownerChild,&MainWidget::slotMoveGroupTo);
    connect(removeFromList,&QAction::triggered,ownerChild,&MainWidget::slotDeleteItemFromMessageList);
}

void StaticIniator::initGroupSectionMenu(QMenu *menu,QWidget * owner)
{
    MainWidget * ownerChild = dynamic_cast<MainWidget*>(owner);
    menu->setObjectName("groupSectionMenu");

    QIcon icon = QIcon(zsj::global::TransparentMenuIconPath);
    QAction * logoShow = new QAction(icon, "图标显示",menu);
    QAction * listShow = new QAction(icon, "列表显示",menu);
    QAction * visitWeb = new QAction(icon, "访问MQ官网",menu);
    QAction * addGroup = new QAction(icon, "添加查找群",menu);
    QAction * createGroup = new QAction(icon, "创建一个群",menu);
    QAction * addGroupSection = new QAction(icon, "添加群分组",menu);
    QAction * renameGroupSection = new QAction(icon, "重命名群分组",menu);
    QAction * deleteGroupSection = new QAction(icon, "删除群分组",menu);

    menu->addAction(logoShow);
    menu->addAction(listShow);
    menu->addSeparator();
    menu->addAction(visitWeb);
    menu->addSeparator();
    menu->addAction(addGroup);
    menu->addAction(createGroup);
    menu->addSeparator();
    menu->addAction(addGroupSection);
    menu->addAction(renameGroupSection);
    menu->addAction(deleteGroupSection);

    initMenusStyle(menu);

    connect(addGroup,&QAction::triggered,ownerChild,&MainWidget::slotFindAndAddGroup);
    connect(createGroup,&QAction::triggered,ownerChild,&MainWidget::slotCreateGroup);
    connect(addGroupSection,&QAction::triggered,ownerChild,&MainWidget::slotAddGroupSection);
    connect(renameGroupSection,&QAction::triggered,ownerChild,&MainWidget::slotRenameGroupSection);
    connect(deleteGroupSection,&QAction::triggered,ownerChild,&MainWidget::slotDeleteGroupSection);
}


void zsj::StaticIniator::initMenusStyle(QMenu * menu)
{
    // Qt::NoDropShadowWindowHint  设置窗口没有阴影
    menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground);
    menu->setStyleSheet(zsj::ReadQStyleSheet::readQss("://css/userMenu.css"));
}

void StaticIniator::initSendMenu(QMenu *menu, QWidget *owner)
{
    ChatWidget * ownerChild = dynamic_cast<ChatWidget*>(owner);
    menu->setObjectName("sendMenu");
    QIcon icon = QIcon(zsj::global::TransparentMenuIconPath);
    QActionGroup * actionGroup = new QActionGroup(ownerChild);
    actionGroup->setExclusive(true);

    QAction * actionEnter = new QAction("按Enter键发送消息",actionGroup);
    actionEnter->setCheckable(true);
    actionEnter->setChecked(true);
    QAction * actionCtrlEnter = new QAction("按Ctrl+Enter键发送消息",actionGroup);
    actionCtrlEnter->setCheckable(true);

    menu->addAction(actionEnter);
    menu->addAction(actionCtrlEnter);








    initMenusStyle(menu);

    connect(actionEnter,&QAction::triggered,ownerChild,&ChatWidget::slotChooseEnter);
    connect(actionCtrlEnter,&QAction::triggered,ownerChild,&ChatWidget::slotChooseCtrlEnter);

}

}



