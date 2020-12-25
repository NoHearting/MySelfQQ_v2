#include "StaticIniator.h"
#include "MainWidget.h"
#include "ReadQStyleSheet.h"

#include <QMutex>
#include <QMutexLocker>

namespace zsj {

QScopedPointer<StaticIniator> StaticIniator::staticIniator;

StaticIniator *StaticIniator::Instatcne()
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
    MainWidget * ownerChild = dynamic_cast<MainWidget*>(owner);
    menu->setObjectName("userMenu");
    menu->addAction(QIcon(":/main/res/main/message.png"), "发送即时消息", ownerChild, SLOT(sendMessage()));
    menu->addAction("发送电子邮件", ownerChild, SLOT(sendEmail()));
    menu->addSeparator();
    menu->addAction("查看资料");
    menu->addAction("消息免打扰", ownerChild, SLOT(messageAvoid()));
    menu->addAction("分享他的名片");
    menu->addAction(QIcon(":/main/res/main/message-record.png"), "消息记录", ownerChild, SLOT(messageRecord()));
    menu->addSeparator();
    menu->addAction("设置权限", ownerChild, SLOT(setPrivilege()));
    menu->addAction(QIcon(":/main/res/main/update-remark.png"), "修改好友备注", ownerChild, SLOT(updateRemark()));
    menu->addAction(QIcon(":/main/res/main/move-friends.png"), "移动联系人至", ownerChild, SLOT(moveFriend()));
    menu->addAction(QIcon(":/main/res/main/delete-friend.png"), "删除好友", ownerChild, SLOT(deleteFriend()));
    menu->addAction("举报此用户", ownerChild, SLOT(reportFriend()));
    menu->addAction(QIcon(":/main/res/main/friend-manager.png"), "好友管理", ownerChild, SLOT(friendManager()));
    menu->addSeparator();
    menu->addAction("会员快捷功能", ownerChild, SLOT(vipFunction()));
    menu->addAction(QIcon(":/main/res/main/space.png"), "进入MQ空间", ownerChild, SLOT(intoSpace()));

    initMenusStyle(menu);
}

void StaticIniator::initFirendSectionMenu(QMenu *menu,QWidget * owner)
{
    MainWidget * ownerChild = dynamic_cast<MainWidget*>(owner);
    menu->setObjectName("sectionMenu");
    menu->addAction("刷新好友列表", ownerChild, SLOT(updateFriendList()));
    menu->addAction("显示在线联系人", ownerChild, SLOT(showOnlineFriends()));
    menu->addSeparator();
    menu->addAction("隐身对该分组可见", ownerChild, SLOT(hideToShowTheSection()));
    menu->addAction("在线对该分组隐身", ownerChild, SLOT(onlineToHideTheSection()));
    menu->addSeparator();
    menu->addAction("添加分组", ownerChild, SLOT(addSection()));
    menu->addAction("重命名", ownerChild, SLOT(renameSection()));
    menu->addAction(QIcon(":/main/res/main/delete-section.png"), "删除该组", ownerChild, SLOT(deleteSection()));
    menu->addAction(QIcon(":/main/res/main/friend-manager.png"), "好友管理器", ownerChild, SLOT(friendManager()));

    initMenusStyle(menu);
}

void StaticIniator::initGroupMenu(QMenu *menu,QWidget * owner)
{
    MainWidget * ownerChild = dynamic_cast<MainWidget*>(owner);
    menu->setObjectName("groupMenu");
    menu->addAction("发送群消息", ownerChild, SLOT(sendGroupMessage()));
    menu->addSeparator();
    menu->addAction(QIcon(":/main/res/main/group-data.png"),"查看群资料", ownerChild, SLOT(showGroupInfo()));
    menu->addAction("群消息设置", ownerChild, SLOT(groupMessageSetting()));
    menu->addAction("查看消息记录", ownerChild, SLOT(messageRecord()));
    menu->addSeparator();
    menu->addAction(QIcon(":/main/res/main/update-remark.png"), "修改群备注", ownerChild, SLOT(updateGroupRemark()));
    menu->addAction("生成桌面快捷方式", ownerChild, SLOT(createDesktopShortcut()));
    menu->addAction("移动群至", ownerChild, SLOT(cancelIsTop()));
    menu->addSeparator();
    menu->addAction("如何升级", ownerChild, SLOT(howToUpgrade()));
    menu->addAction("退出该群", ownerChild, SLOT(exitTheGroup()));
    menu->addAction("举报该群", ownerChild, SLOT(reportGroup()));

    initMenusStyle(menu);
}

void StaticIniator::initGroupSectionMenu(QMenu *menu,QWidget * owner)
{
    MainWidget * ownerChild = dynamic_cast<MainWidget*>(owner);
    menu->setObjectName("groupSectionMenu");
    menu->addAction("图标显示", ownerChild, SLOT(iconShow()));
    menu->addAction("列表显示", ownerChild, SLOT(listShow()));
    menu->addSeparator();
    menu->addAction("访问MQ群官网", ownerChild, SLOT(visitMQOfficialWebsite()));
    menu->addSeparator();
    menu->addAction("查找添加群", ownerChild, SLOT(findAndAddGroup()));
    menu->addAction("创建一个群", ownerChild, SLOT(createGroup()));
    menu->addSeparator();
    menu->addAction("添加群分组", ownerChild, SLOT(addGroupSection()));
    menu->addAction("重命名群分组", ownerChild, SLOT(renameGroupSection()));
    menu->addAction("删除群分组", ownerChild, SLOT(deleteGroupSection()));

    initMenusStyle(menu);
}

void StaticIniator::initMessageListFirendMenu(QMenu *menu,QWidget * owner)
{
    MainWidget * ownerChild = dynamic_cast<MainWidget*>(owner);
    menu->setObjectName("listUserMenu");
    menu->addAction(QIcon(":/main/res/main/message.png"), "发送即时消息", ownerChild, SLOT(sendMessage()));
    menu->addAction("发送电子邮件", ownerChild, SLOT(sendEmail()));
    menu->addSeparator();
    menu->addAction("查看资料");
    menu->addAction("消息免打扰", ownerChild, SLOT(messageAvoid()));
    menu->addAction("分享他的名片");
    menu->addAction(QIcon(":/main/res/main/message-record.png"), "消息记录", ownerChild, SLOT(messageRecord()));
    menu->addSeparator();
    menu->addAction("从会话列表中移除",ownerChild,SLOT(deleteItemFromMessageList()));
    menu->addAction("设置权限", ownerChild, SLOT(setPrivilege()));
    menu->addAction(QIcon(":/main/res/main/update-remark.png"), "修改好友备注", ownerChild, SLOT(updateRemark()));
    menu->addAction(QIcon(":/main/res/main/move-friends.png"), "移动联系人至", ownerChild, SLOT(moveFriend()));
    menu->addAction(QIcon(":/main/res/main/delete-friend.png"), "删除好友", ownerChild, SLOT(deleteFriend()));
    menu->addAction("举报此用户", ownerChild, SLOT(reportFriend()));
    menu->addAction(QIcon(":/main/res/main/friend-manager.png"), "好友管理", ownerChild, SLOT(friendManager()));
    menu->addSeparator();
    menu->addAction("会员快捷功能", ownerChild, SLOT(vipFunction()));
    menu->addAction(QIcon(":/main/res/main/space.png"), "进入MQ空间", ownerChild, SLOT(intoSpace()));

    initMenusStyle(menu);
}

void StaticIniator::initMessageListGroupMenu(QMenu *menu,QWidget * owner)
{
    MainWidget * ownerChild = dynamic_cast<MainWidget*>(owner);
    menu->setObjectName("listGroupMenu");
    menu->addAction("发送群消息", ownerChild, SLOT(sendGroupMessage()));
    menu->addSeparator();
    menu->addAction(QIcon(":/main/res/main/group-data.png"),"查看群资料", ownerChild, SLOT(showGroupInfo()));
    menu->addAction("群消息设置", ownerChild, SLOT(groupMessageSetting()));
    menu->addAction("查看消息记录", ownerChild, SLOT(messageRecord()));
    menu->addSeparator();
    menu->addAction("从会话列表中移除",ownerChild,SLOT(deleteItemFromMessageList()));
    menu->addAction(QIcon(":/main/res/main/update-remark.png"), "修改群备注", ownerChild, SLOT(updateGroupRemark()));
    menu->addAction("生成桌面快捷方式", ownerChild, SLOT(createDesktopShortcut()));
    menu->addAction("移动群至", ownerChild, SLOT(cancelIsTop()));
    menu->addSeparator();
    menu->addAction("如何升级", ownerChild, SLOT(howToUpgrade()));
    menu->addAction("退出该群", ownerChild, SLOT(exitTheGroup()));
    menu->addAction("举报该群", ownerChild, SLOT(reportGroup()));

    initMenusStyle(menu);
}

void zsj::StaticIniator::initMenusStyle(QMenu * menu)
{
    // Qt::NoDropShadowWindowHint  设置窗口没有阴影
    menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground);
    menu->setStyleSheet(zsj::ReadQStyleSheet::readQss("://css/userMenu.css"));
}

}



