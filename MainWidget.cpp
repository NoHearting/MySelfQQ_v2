#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "ReadQStyleSheet.h"
#include "Util.h"
#include "MessageItemWidget.h"
#include "UserData.h"
#include "GroupData.h"
#include "StaticIniator.h"


#include <QDebug>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QScrollBar>
#include <utility>



MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    initObjects();
    initResourceAndForm();
    initSignalsAndSlots();

#ifdef DEBUG
    setHead(":/test/res/test/head3.jpg");
#endif
}

MainWidget::~MainWidget()
{
    delete ui;
}



void MainWidget::initObjects()
{
    frameless = new zsj::Frameless(this);
    systemTray = new zsj::SystemTray(this);
    friendDialog = new WarnDialog(this);
    groupDialog = new WarnDialog(this);
    initMenus();
}



void MainWidget::initResourceAndForm()
{
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    frameless->setPadding(2);
    frameless->setWidget(this);      //设置窗口可移动，可扩展

    systemTray->showSystemTray();
    QPixmap *trayIcon = new QPixmap(":/global/res/global/water-tray.png");
    systemTray->setSystemTrayIcon(trayIcon);
    this->setStyleSheet("");
    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("://css/main.css"));


    //设置窗口阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);  //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(12);     //阴影的模糊半径
    ui->widgetMain->setGraphicsEffect(shadow);

    //选中第一个消息页面
    switchToMessageWidget();
//    switchToLinkmanWidget();

    // 初始化好友列表
    ui->treeWidgetFriend->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->treeWidgetGroup->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->treeWidgetFriend->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->treeWidgetGroup->setContextMenuPolicy(Qt::CustomContextMenu);
    initManlinkFriend();
    initManlinkGroup();

    // 初始化消息列表
    ui->listWidgetMessage->setContextMenuPolicy(Qt::CustomContextMenu);
    initMessageList();

    // 初始化搜索框的搜索图标
    QAction *action = new QAction(ui->lineEditSearch);
    action->setIcon(QIcon(":/main/res/main/search.png"));
    ui->lineEditSearch->addAction(action, QLineEdit::LeadingPosition);

    ui->labelNickname->adjustSize();

}

void MainWidget::initSignalsAndSlots()
{
    // ---------- 顶部功能按钮 -----------------
    connect(ui->toolButtonClose, &QToolButton::clicked, this, &MainWidget::closeWindow);
    qInfo() << "connect QToolButton::clicked to MainWidget::closeWindow";

    connect(ui->toolButtonMin, &QToolButton::clicked, this, &MainWidget::minWindow);
    qInfo() << "connect toolButtonMin::clicked to MainWidget::minWindow";

    connect(ui->toolButtonAdd, &QToolButton::clicked, this, &MainWidget::interfaceManager);
    qInfo() << "connect ui->toolButtonAdd::clicked to MainWidget::interfaceManager";

    connect(systemTray, &zsj::SystemTray::sigOpenWindow, this, &MainWidget::show);
    qInfo() << "connect systemTray::sigOpenWindow to MainWidget::show";

    connect(ui->pushButtonMessage, &QPushButton::clicked, this, &MainWidget::switchToMessageWidget);
    qInfo() << "connect ui->pushButtonMessage::clicked to MainWidget::switchToMessageWidget";

    connect(ui->pushButtonLinkman, &QPushButton::clicked, this, &MainWidget::switchToLinkmanWidget);
    qInfo() << "connect ui->pushButtonLinkman::clicked to MainWidget::switchToLinkmanWidget";

    connect(ui->pushButtonSpace, &QPushButton::clicked, this, &MainWidget::switchToSpaceWidget);
    qInfo() << "connect ui->pushButtonSpace::clicked to MainWidget::switchToSpaceWidget";

    connect(ui->treeWidgetFriend, &QTreeWidget::itemClicked, this, &MainWidget::treeWidgetItemClick);
    connect(ui->treeWidgetGroup, &QTreeWidget::itemClicked, this, &MainWidget::treeWidgetItemClick);
    qInfo() << "connect ui->treeWidgetGroup,ui->treeWidgetFriend::itemClicked to MainWidget::treeWidgetItemClick";

    connect(ui->treeWidgetFriend, &QTreeWidget::itemExpanded, this, &MainWidget::expanded);
    connect(ui->treeWidgetGroup, &QTreeWidget::itemExpanded, this, &MainWidget::expanded);
    qInfo() << "connect treeWidgetFriend,treeWidgetGroup::itemExpanded to MainWidget::expanded";
    connect(ui->treeWidgetFriend, &QTreeWidget::itemCollapsed, this, &MainWidget::collasped);
    connect(ui->treeWidgetGroup, &QTreeWidget::itemCollapsed, this, &MainWidget::collasped);
    qInfo() << "connect treeWidgetFriend,treeWidgetGroup::itemExpanded to MainWidget::collasped`";

    connect(ui->treeWidgetFriend, &MyTreeWidget::customContextMenuRequested, this, &MainWidget::showContextMenuFriend);
    connect(ui->treeWidgetGroup, &MyTreeWidget::customContextMenuRequested, this, &MainWidget::showContextMenuGroup);
    qInfo() << "connect treeWidgetFriend,treeWidgetGroup::customContextMenuRequested to MainWidget::showContextMenuFriend,showContextMenuGroup";

    connect(ui->listWidgetMessage, &MyListWidget::customContextMenuRequested, this, &MainWidget::showContextMenuMessage);
    qInfo() << "connect listWidgetMessage::customContextMenuRequested to MainWidget::showContextMenuMessage";
}

void MainWidget::initManlinkFriend()
{
    // 设置为没有缩进
    ui->treeWidgetFriend->setIndentation(0);



    QTreeWidgetItem *rootFriends = this->addTreeWidgetRootNode(ui->treeWidgetFriend, "我的好友", 3, 12);
    dataFriend.insert(std::make_pair(rootFriends, std::list<QTreeWidgetItem *>()));
    QTreeWidgetItem *rootStangers = this->addTreeWidgetRootNode(ui->treeWidgetFriend, "陌生人", 4, 6);
    dataFriend.insert(std::make_pair(rootStangers, std::list<QTreeWidgetItem *>()));
    QTreeWidgetItem *rootNull = this->addTreeWidgetRootNode(ui->treeWidgetFriend, "", 0, 0);
    dataFriend.insert(std::make_pair(rootNull, std::list<QTreeWidgetItem *>()));
    QPixmap head(":/test/res/test/head2.jpg");
    zsj::UserData::ptr user1(new zsj::UserData(head, "猪123123123头1", "1231231", "签名1", "备注1"));
    zsj::UserData::ptr user2(new zsj::UserData(head, "狗头1", "1231231", "签名2", "备注2"));
    this->addTreeWidgetChildNode(ui->treeWidgetFriend, rootFriends, user1);
    this->addTreeWidgetChildNode(ui->treeWidgetFriend, rootFriends, user2);

    QPixmap head2(":/test/res/test/head3.jpg");
    zsj::UserData::ptr user3(new zsj::UserData(head2, "陌生人1", "1231231", "签名1", "备注1"));
    zsj::UserData::ptr user4(new zsj::UserData(head2, "陌生人2", "1231231", "签名2", "备注2"));
    this->addTreeWidgetChildNode(ui->treeWidgetFriend, rootStangers, user3);
    this->addTreeWidgetChildNode(ui->treeWidgetFriend, rootStangers, user4);

    for(int i = 0; i < 15; i++)
    {
        QPixmap head3(QString(":/test/res/test/head%1.jpg").arg(i % 5));
        zsj::UserData::ptr user3(new zsj::UserData(head3, QString("狗头%1").arg(i),
                                 "1231231", QString("签名%1").arg(i), QString("备注%1").arg(i)));
        this->addTreeWidgetChildNode(ui->treeWidgetFriend, rootFriends, user3);
    }
}

void MainWidget::initManlinkGroup()
{
    // 设置为没有缩进
    ui->treeWidgetGroup->setIndentation(0);

    QTreeWidgetItem *rootTop = this->addTreeWidgetRootNode(ui->treeWidgetGroup, "置顶群聊", 3, 3);
    QTreeWidgetItem *rootMy = this->addTreeWidgetRootNode(ui->treeWidgetGroup, "我的群聊", 10, 59);
    QTreeWidgetItem *rootMultile = this->addTreeWidgetRootNode(ui->treeWidgetGroup, "我的多人聊天", 4, 4);
    QTreeWidgetItem *rootNull = this->addTreeWidgetRootNode(ui->treeWidgetGroup, "", 0, 0);
    dataGroup.insert(std::make_pair(rootTop, std::list<QTreeWidgetItem *>()));
    dataGroup.insert(std::make_pair(rootMy, std::list<QTreeWidgetItem *>()));
    dataGroup.insert(std::make_pair(rootMultile, std::list<QTreeWidgetItem *>()));
    dataGroup.insert(std::make_pair(rootNull, std::list<QTreeWidgetItem *>()));

    qDebug() << "init root";
    QPixmap head1(":/test/res/test/head4.jpg");
    zsj::GroupData::ptr group1(new zsj::GroupData(head1, "富婆交流会所", "123", "群介绍", 0, 0));
    zsj::GroupData::ptr group2(new zsj::GroupData(head1, "2017级计科专业", "123", "群介绍", 0, 0));
    zsj::GroupData::ptr group3(new zsj::GroupData(head1, "星耀2020，信服起航！", "123", "群介绍", 0, 0));
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootTop, group1, "昨天");
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootTop, group2, "7:30");
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootTop, group3, "12-15");

    QPixmap head2(":/test/res/test/head4.jpg");
    zsj::GroupData::ptr group4(new zsj::GroupData(head2, "老污群", "123", "群介绍", 0, 0));
    zsj::GroupData::ptr group5(new zsj::GroupData(head2, "2017级计科专业", "123", "群介绍", 0, 0));
    zsj::GroupData::ptr group6(new zsj::GroupData(head2, "sylar技术群", "123", "群介绍", 0, 0));
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootMy, group4, "11-28");
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootMy, group5, "7:30");
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootMy, group6, "16:17");

    QPixmap head3(":/test/res/test/head3.jpg");
    QPixmap headNull;
    zsj::GroupData::ptr group7(new zsj::GroupData(headNull, "项管-鲁嘉嘉、无心", "123", "群介绍", 0, 0));
    zsj::GroupData::ptr group8(new zsj::GroupData(head3, "张家豪、中秋、无心", "123", "群介绍", 0, 0));
    zsj::GroupData::ptr group9(new zsj::GroupData(head3, "无心", "123", "群介绍", 0, 0));
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootMultile, group7, "2017-12-1");
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootMultile, group8, "201711-11");
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootMultile, group9, "2017-6-3");
}

void MainWidget::initMessageList()
{
    for(int i = 0; i < 15; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidgetMessage);
        ui->listWidgetMessage->addItem(item);
        item->setSizeHint(QSize(ui->widgetMiddle->width(), 60));
        QPixmap head(":/test/res/test/head2.jpg");
        MessageItemWidget *messageItem = new MessageItemWidget(head, QString("昵称%1").arg(i), QString("消息%1").arg(i),
                QString("7-%1").arg(i), i % 2, i % 2, (i % 2 ? DataType::GROUP_DATA : DataType::USER_DATA), ui->listWidgetMessage);
        ui->listWidgetMessage->setItemWidget(item, messageItem);
    }
}

void MainWidget::initMenus()
{
    userMenu = new QMenu();
    zsj::StaticIniator::Instatcne()->initFirendMenu(userMenu, this);

    sectionMenu = new QMenu();
    zsj::StaticIniator::Instatcne()->initFirendSectionMenu(sectionMenu, this);

    groupMenu = new QMenu();
    zsj::StaticIniator::Instatcne()->initGroupMenu(groupMenu, this);

    groupSectionMenu = new QMenu();
    zsj::StaticIniator::Instatcne()->initGroupSectionMenu(groupSectionMenu, this);

    moveSubMenu = new QMenu();
    moveSubMenu->setObjectName("moveSubMenu");
    connect(moveSubMenu, &QMenu::triggered, this, &MainWidget::moveItem);
    zsj::StaticIniator::Instatcne()->initMenusStyle(moveSubMenu);
}

QTreeWidgetItem *MainWidget::addTreeWidgetRootNode(QTreeWidget *treeWidget, LinkmanGroupWidget *group)
{
    if(nullptr != treeWidget && nullptr != group)
    {
        QTreeWidgetItem *rootNode = new QTreeWidgetItem(treeWidget);
        rootNode->setData(0, Qt::UserRole, 0);

        treeWidget->addTopLevelItem(rootNode);
        treeWidget->setItemWidget(rootNode, 0, group);
        return rootNode;
    }
    else
    {
        qCritical() << "QTreeWidget Object or LinkmanGroupWidget Object is nullptr!";
        return nullptr;
    }
}

QTreeWidgetItem *MainWidget::addTreeWidgetRootNode(QTreeWidget *treeWidget, const QString &groupName,
        int active, int total)
{
    if(nullptr != treeWidget)
    {
        QTreeWidgetItem *rootNode = new QTreeWidgetItem(treeWidget);
        rootNode->setData(0, Qt::UserRole, 0);
        QPixmap icon(":/main/res/main/arrow-right.png");
        LinkmanGroupWidget *item = new LinkmanGroupWidget(icon, groupName, active, total, treeWidget);
        treeWidget->addTopLevelItem(rootNode);
        treeWidget->setItemWidget(rootNode, 0, item);

        return rootNode;
    }
    else
    {
        qCritical() << "QTreeWidget object is nullptr!";
        return nullptr;
    }
}

QTreeWidgetItem *MainWidget::addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode,
        LinkmanItemWidget *item)
{
    if(nullptr != treeWidget && nullptr != rootNode && nullptr != item )
    {
        QTreeWidgetItem *child = new QTreeWidgetItem(rootNode);
        child->setData(0, Qt::UserRole, 1);
        rootNode->addChild(child);
        treeWidget->setItemWidget(child, 0, item);
        dataFriend[rootNode].push_back(child);
        return child;
    }
    else
    {
        qCritical() << "QTreeWidget,QTreeWidgetItem,LinkmanItemWidget Object is nullptr!";
        return nullptr;
    }

}

QTreeWidgetItem *MainWidget::addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode,
        zsj::UserData::ptr userData)
{
    if(nullptr != treeWidget && nullptr != rootNode)
    {
        QTreeWidgetItem *child = new QTreeWidgetItem(rootNode);
        child->setData(0, Qt::UserRole, 1);
        LinkmanItemWidget *item = new LinkmanItemWidget(userData, treeWidget);
        rootNode->addChild(child);
        treeWidget->setItemWidget(child, 0, item);
        dataFriend[rootNode].push_back(child);
        return child;
    }
    else
    {
        qCritical() << "QTreeWidget,QTreeWidgetItem- Object is nullptr!";
        return nullptr;
    }
}

QTreeWidgetItem *MainWidget::addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode,
        zsj::GroupData::ptr groupData, const QString &date)
{
    if(nullptr != treeWidget && nullptr != rootNode)
    {
        QTreeWidgetItem *child = new QTreeWidgetItem(rootNode);
        child->setData(0, Qt::UserRole, 1);
        LinkmanGroupItemWidget *item = new LinkmanGroupItemWidget(groupData, date, treeWidget);
        rootNode->addChild(child);
        treeWidget->setItemWidget(child, 0, item);
        dataGroup[rootNode].push_back(child);
        return child;
    }
    else
    {
        qCritical() << "QTreeWidget,QTreeWidgetItem- Object is nullptr!";
        return nullptr;
    }
}

void MainWidget::setHead(QPixmap &pixmap)
{
    QPixmap scaled = zsj::scaledPixmap(pixmap, zsj::HeadSize::mainDiamter, zsj::HeadSize::mainDiamter);
    QPixmap result = zsj::pixmapToRound(scaled, zsj::HeadSize::mainDiamter / 2);
    ui->labelHead->setPixmap(result);
}

void MainWidget::setHead(const QString &pixmapPath)
{
    QPixmap origin(pixmapPath);
    setHead(origin);
}

void MainWidget::deleteTreeWidgetItem(QTreeWidgetItem *item, std::map<QTreeWidgetItem *, std::list<QTreeWidgetItem *>> &data)
{
    if(item != nullptr)
    {
        bool isChild = item->data(0, Qt::UserRole).toBool();
        qDebug() << "进入 " << item->childCount();
        // 为子项目
        if(isChild)
        {
            auto parent = item->parent();
            for(auto it = data[parent].begin(); it != data[parent].end(); ++it)
            {
                if(*it == item)
                {
                    data[parent].erase(it);
                    delete *it;
                    break;
                }
            }
        }
        else
        {
            for(auto it = data.begin(); it != data.end(); ++it)
            {
                qDebug() << "--";
                if(it->first == item)
                {
                    qDebug() << "find it";
                    for(auto &itemWidget : it->second)
                    {
                        delete itemWidget;
                    }
                    delete it->first;
                    data.erase(it);
                    break;
                }
            }
        }
    }
}

void MainWidget::showFriendMenu()
{
    auto actions = userMenu->actions();
    qDebug() << actions.size();
    for(auto &item : actions)
    {
//        qDebug() << item->text();
        if(item->text() == "从会话列表中移除")
        {
            item->setVisible(false);
        }
        else if(item->text() == "移动联系人至")
        {
            // 添加子菜单
            qDebug() << item->text();
            if(item->menu() == nullptr)
            {
                qDebug() << "添加子菜单";
                updateSubMenu(moveSubMenu, ui->treeWidgetFriend, dataFriend);
                item->setMenu(moveSubMenu);
                userMenu->addMenu(moveSubMenu);
            }
            else  // 刷新子菜单
            {
                qDebug() << "刷新子菜单";
                updateSubMenu(moveSubMenu, ui->treeWidgetFriend, dataFriend);
            }
        }
    }
    userMenu->exec(this->cursor().pos());
}

void MainWidget::showMessageListFriendMenu()
{
    auto actions = userMenu->actions();
    qDebug() << actions.size();
    for(auto &item : actions)
    {
        if(item->text() == "从会话列表中移除")
        {
            item->setVisible(true);
        }
        else if(item->text() == "移动联系人至")
        {
            // 添加子菜单
            qDebug() << item->text();
            if(item->menu() == nullptr)
            {
                qDebug() << "添加子菜单";
                updateSubMenu(moveSubMenu, ui->treeWidgetFriend, dataFriend);
                item->setMenu(moveSubMenu);
                userMenu->addMenu(moveSubMenu);
            }
            else  // 刷新子菜单
            {
                qDebug() << "刷新子菜单";
                updateSubMenu(moveSubMenu, ui->treeWidgetFriend, dataFriend);
            }
        }
    }
    userMenu->exec(this->cursor().pos());
}

void MainWidget::showFriendSectionMenu()
{
    auto actions = sectionMenu->actions();
    qDebug() << actions.size();
    for(auto &item : actions)
    {
        if(item->text() == "删除该组")
        {
            item->setEnabled(true);
            break;
        }
    }
    sectionMenu->exec(this->cursor().pos());
}

void MainWidget::showDefaultFriendSectionMenu()
{
    auto actions = sectionMenu->actions();
    qDebug() << actions.size();
    for(auto &item : actions)
    {
        if(item->text() == "删除该组")
        {
            item->setEnabled(false);
            break;
        }
    }
    sectionMenu->exec(this->cursor().pos());
}

void MainWidget::showGroupMenu()
{
    auto actions = groupMenu->actions();
    qDebug() << actions.size();
    for(auto &item : actions)
    {
        if(item->text() == "从会话列表移除")
        {
            item->setVisible(false);
            break;
        }
    }
    groupMenu->exec(this->cursor().pos());
}

void MainWidget::showMessageListGroupMenu()
{
    auto actions = groupMenu->actions();
    qDebug() << actions.size();
    for(auto &item : actions)
    {
        if(item->text() == "从会话列表移除")
        {
            item->setVisible(true);
            break;
        }
    }
    groupMenu->exec(this->cursor().pos());
}

void MainWidget::showGroupSectionMenu()
{
    auto actions = groupSectionMenu->actions();
    qDebug() << actions.size();
    for(auto &item : actions)
    {
        if(item->text() == "重命名群分组" || item->text() == "删除群分组")
        {
            item->setEnabled(true);
        }
    }
    groupSectionMenu->exec(this->cursor().pos());
}

void MainWidget::showDefaultGroupSectionMenu()
{
    auto actions = groupSectionMenu->actions();
    qDebug() << actions.size();
    for(auto &item : actions)
    {
        if(item->text() == "重命名群分组" || item->text() == "删除群分组")
        {
            item->setEnabled(false);
        }
    }
    groupSectionMenu->exec(this->cursor().pos());
}

void MainWidget::updateSubMenu(QMenu *menu, QTreeWidget *treeWidget, std::map<QTreeWidgetItem *, std::list<QTreeWidgetItem *> > &data)
{
    menu->clear();
    for(auto &item : data)
    {
        QWidget *widget = treeWidget->itemWidget(item.first, 0);
        LinkmanGroupWidget *itemSection = dynamic_cast<LinkmanGroupWidget *>(widget);
        if(itemSection != nullptr)
        {
            menu->addAction(itemSection->getGrouoName());
        }
    }
}

void MainWidget::closeWindow()
{
    qApp->quit();
}

void MainWidget::minWindow()
{
    this->hide();
}

void MainWidget::interfaceManager()
{
//    ui->toolButtonEmail->hide();
    bool isShow = ui->toolButtonEmail->isHidden();
    ui->toolButtonEmail->setHidden(!isShow);
}

void MainWidget::switchToMessageWidget()
{
    if(ui->stackedWidget->currentIndex() != 0)
    {
        ui->pushButtonMessage->setChecked(true);
        ui->pushButtonLinkman->setChecked(false);
        ui->pushButtonSpace->setChecked(false);
        ui->stackedWidget->forwordWidget();
    }
}

void MainWidget::switchToLinkmanWidget()
{
    if(ui->stackedWidget->currentIndex() != 1)
    {
        ui->pushButtonMessage->setChecked(false);
        ui->pushButtonLinkman->setChecked(true);
        ui->pushButtonSpace->setChecked(false);
        ui->stackedWidget->nextWidget();
    }
}

void MainWidget::switchToSpaceWidget()
{
    ui->pushButtonMessage->setChecked(false);
    ui->pushButtonLinkman->setChecked(false);
    ui->pushButtonSpace->setChecked(true);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWidget::treeWidgetItemClick(QTreeWidgetItem *item, int)
{
    bool isChild = item->data(0, Qt::UserRole).toBool();
    //判断是否为父节点
    if(false == isChild)
    {
        bool opened = item->isExpanded();
        item->setExpanded(!opened);
        item->setSelected(false);
    }
}

void MainWidget::collasped(QTreeWidgetItem *item)
{
    bool isChild = item->data(0, Qt::UserRole).toBool();
    if(false == isChild)
    {
        QTreeWidget *treeWidget = item->treeWidget();
        if(nullptr != treeWidget)
        {
            QWidget *itemWidget = treeWidget->itemWidget(item, 0);
            if(nullptr != itemWidget)
            {
                LinkmanGroupWidget *groupWidget = dynamic_cast<LinkmanGroupWidget *>(itemWidget);
                if(groupWidget != nullptr)
                {
                    groupWidget->setIcon(":/main/res/main/arrow-right.png");
                }
                else
                {
                    qCritical() << "dynamic_cast failed";
                }
            }
            else
            {
                qCritical() << "no item widget";
            }
        }
        else
        {
            qCritical() << "tree widget is null";
        }

    }
}

void MainWidget::expanded(QTreeWidgetItem *item)
{
    bool isChild = item->data(0, Qt::UserRole).toBool();
    if(false == isChild)
    {
        QTreeWidget *treeWidget = item->treeWidget();
        if(nullptr != treeWidget)
        {
            QWidget *itemWidget = treeWidget->itemWidget(item, 0);
            if(nullptr != itemWidget)
            {
                LinkmanGroupWidget *groupWidget = dynamic_cast<LinkmanGroupWidget *>(itemWidget);
                if(groupWidget != nullptr)
                {
                    groupWidget->setIcon(":/main/res/main/arrow-down.png");
                }
                else
                {
                    qCritical() << "dynamic_cast failed";
                }
            }
            else
            {
                qCritical() << "no item widget";
            }
        }
        else
        {
            qCritical() << "tree widget is null";
        }
    }

}

void MainWidget::showContextMenuFriend(const QPoint &point)
{
    QTreeWidgetItem *item = ui->treeWidgetFriend->itemAt(point);
    if(nullptr != item)
    {
        itemUser = item;
        itemGroup = nullptr;
        itemMessage = nullptr;

        qDebug() << "record itemUser";
        bool isChild = item->data(0, Qt::UserRole).toBool();
        if(isChild)
        {
//            userMenu->exec(this->cursor().pos());
            showFriendMenu();
        }
        else
        {
            QWidget *widget = ui->treeWidgetFriend->itemWidget(item, 0);
            LinkmanGroupWidget *itemWidget = dynamic_cast<LinkmanGroupWidget *>(widget);

            // 默认分组名称可以变，这里的判别手段需要后期加上数据之后用其他的
            // 标志来判断是否该分组是否为默认分组
            qDebug() << itemWidget->getGrouoName();
            if(itemWidget->getGrouoName() == "我的好友")
            {
                showDefaultFriendSectionMenu();
            }
            else
            {
                showFriendSectionMenu();
            }
        }

    }
    else
    {
        qCritical() << "invalid QTreeWidgetItem";
    }

}

void MainWidget::showContextMenuGroup(const QPoint &point)
{
    QTreeWidgetItem *item = ui->treeWidgetGroup->itemAt(point);
    if(nullptr != item)
    {
        itemGroup = item;
        itemUser = nullptr;
        itemMessage = nullptr;

        qDebug() << "record itemGroup";
        bool isChild = item->data(0, Qt::UserRole).toBool();
        if(isChild)
        {
            showGroupMenu();
        }
        else
        {
            QWidget *widget = ui->treeWidgetGroup->itemWidget(item, 0);
            LinkmanGroupWidget *itemWidget = dynamic_cast<LinkmanGroupWidget *>(widget);
            // 默认分组名称可以变，这里的判别手段需要后期加上数据之后用其他的
            // 标志来判断是否该分组是否为默认分组
            if(itemWidget->getGrouoName() == "我的群聊")
            {
                qDebug() << "我的群聊";
                showDefaultGroupSectionMenu();
            }
            else
            {
                showGroupSectionMenu();
            }
        }

    }
    else
    {
        qCritical() << "invalid QTreeWidgetItem";
    }
}

void MainWidget::showContextMenuMessage(const QPoint &point)
{
    QListWidgetItem *item = ui->listWidgetMessage->itemAt(point);
    if(nullptr != item)
    {
        QWidget *widget = ui->listWidgetMessage->itemWidget(item);
        MessageItemWidget *messageItem = dynamic_cast<MessageItemWidget *>(widget);
        if(nullptr != messageItem)
        {
            itemMessage = item;
            itemGroup = nullptr;
            itemUser = nullptr;

            qDebug() << "record itemMessage  - " << messageItem->getNickname();
            auto type = messageItem->getType();
            switch(type)
            {
                case DataType::GROUP_DATA:
//                    listGroupMenu->exec(this->cursor().pos());
                    showMessageListGroupMenu();
                    break;
                case DataType::USER_DATA:
//                    listUserMenu->exec(this->cursor().pos());
                    showMessageListFriendMenu();
                    break;
                default:
                    break;
            }
        }
        else
        {
            qCritical() << "get MessageItemWidget failed";
            itemMessage = nullptr;
        }
    }
    else
    {
        qCritical() << "invalid QListWidgetItem";
    }
}

void MainWidget::moveItem(QAction *action)
{
    QString targetSectionName = action->text();
    // 当前需要操作的项
    QTreeWidgetItem *source = nullptr;
    // 操作的容器
    QTreeWidget *treeWidget = nullptr;
    // 操作的数据

    mapTreeItem *data = nullptr;


    if(itemUser)
    {
        source = itemUser;
        treeWidget = ui->treeWidgetFriend;
        data = &dataFriend;
    }
    else
    {
        source = itemGroup;
        treeWidget = ui->treeWidgetGroup;
        data = &dataGroup;
    }
    // 需要移动到的目标分组
    QTreeWidgetItem *targetSection = nullptr;

    // 找到目标分组
    for(auto &treeItem : *data)
    {
        QWidget *widget = treeWidget->itemWidget(treeItem.first, 0);
        LinkmanGroupWidget *itemWidget = dynamic_cast<LinkmanGroupWidget *>(widget);
        if(targetSectionName == itemWidget->getGrouoName())
        {
            targetSection = treeItem.first;
            break;
        }
    }
    // 移动视图
    QTreeWidgetItem *sourceSection = source->parent();
    // 由于QTreeWidgetItem不能重新设置父窗口，
    // 所以需要把之前的删除，然后新建一个item
    QTreeWidgetItem *newItem = nullptr;


    QWidget *widget = treeWidget->itemWidget(source, 0);
    if(widget != nullptr)
    {
        if(itemUser){
            LinkmanItemWidget *itemWidget = dynamic_cast<LinkmanItemWidget *>(widget);
            if(itemWidget == nullptr)
            {
                qDebug() << "QWidget* to LinkmanItemWidget* faild";
                return;
            }
            zsj::UserData::ptr userData = itemWidget->getUserData();
            newItem = addTreeWidgetChildNode(treeWidget, targetSection, userData);
        }
        else{
            LinkmanItemWidget *itemWidget = dynamic_cast<LinkmanItemWidget *>(widget);
            if(itemWidget == nullptr)
            {
                qDebug() << "QWidget* to LinkmanItemWidget* faild";
                return;
            }
            zsj::UserData::ptr userData = itemWidget->getUserData();
            newItem = addTreeWidgetChildNode(treeWidget, targetSection, userData);
        }
    }
    else
    {
        qCritical() << "selected item faild!";
        return;
    }
    sourceSection->removeChild(source);       // 当前分组移除

    // 改变数据
    (*data)[targetSection].push_back(newItem); // 当前分组添加
    for(auto iter = (*data).begin(); iter != (*data).end(); ++iter)
    {
        if(iter->first == source)
        {
            (*data).erase(iter);    // 目标分组移除
            break;
        }
    }
    qDebug() << "更改数据成功";
    delete source;
    source = nullptr;
}

void MainWidget::deleteFriend()
{
    if(nullptr != itemUser)
    {
        deleteTreeWidgetItem(itemUser, dataFriend);
    }
}

void MainWidget::deleteFriendSection()
{
    friendDialog->connect(friendDialog, &WarnDialog::sure, this, [ = ]()
    {
        deleteTreeWidgetItem(itemUser, dataFriend);
        friendDialog->close();
    });
    friendDialog->showDialog("删除分组", "选定的分组即将被删除，组内联系人将会移至系统默认分组\"我的好友\"。\n"
                             "你确定要删除分组吗？");

}

void MainWidget::deleteGroupSection()
{
    qDebug() << "删除群分组";
    groupDialog->connect(groupDialog, &WarnDialog::sure, this, [ = ]()
    {
        qDebug() << "get signal";
        deleteTreeWidgetItem(itemGroup, dataGroup);
        groupDialog->close();
    });
    groupDialog->showDialog("删除群分组", "选定的群分组即将被删除，组内MQ群将会移至系统默认分组\"我的群聊\"。\n"
                            "你确定要删除群分组吗？");
}

void MainWidget::deleteItemFromMessageList()
{
    if(nullptr  != itemMessage)
    {
        int currentRow = ui->listWidgetMessage->row(itemMessage);
        QListWidgetItem *item = ui->listWidgetMessage->takeItem(currentRow);
//        ui->listWidgetMessage->update();
        delete item;
        itemMessage = nullptr;
    }
    else
    {
        qCritical() << "item data itemMessage is nullptr";
    }
}





