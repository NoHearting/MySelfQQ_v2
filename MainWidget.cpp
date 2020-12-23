#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "ReadQStyleSheet.h"
#include "Util.h"
#include "MessageItemWidget.h"
#include "UserData.h"
#include "GroupData.h"


#include <QDebug>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include <QScrollBar>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    initObjects();
    initResourceAndForm();
    initSignalsAndSlots();

#ifdef DEBUG
    setHead(":/test/Z:/default/Pictures/head/head2.jpg");
#endif
}

MainWidget::~MainWidget()
{
    delete ui;
}



void MainWidget::initObjects()
{

}



void MainWidget::initResourceAndForm()
{
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    frameless = new zsj::Frameless(this);
    frameless->setPadding(2);
    frameless->setWidget(this);      //设置窗口可移动，可扩展

    systemTray = new zsj::SystemTray(this);

    systemTray->showSystemTray();
    QPixmap *trayIcon = new QPixmap(":/global/res/global/water-tray.png");
    systemTray->setSystemTrayIcon(trayIcon);
    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("://css/main.css"));


    //设置窗口阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);  //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(12);     //阴影的模糊半径
    ui->widgetMain->setGraphicsEffect(shadow);

    //选中第一个消息页面
//    switchToMessageWidget();
    switchToLinkmanWidget();

    // 初始化好友列表

//    ui->treeWidgetFriend->verticalScrollBar()->set
    ui->treeWidgetFriend->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    initManlinkFriend();
    initManlinkGroup();

    // 初始化消息列表
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
}

void MainWidget::initManlinkFriend()
{
    // 设置为没有缩进
    ui->treeWidgetFriend->setIndentation(0);


    QTreeWidgetItem *rootFriends = this->addTreeWidgetRootNode(ui->treeWidgetFriend, "我的好友", 3, 12);
    QTreeWidgetItem *rootStangers = this->addTreeWidgetRootNode(ui->treeWidgetFriend, "陌生人", 4, 6);
    QPixmap head(":/test/Z:/default/Pictures/head/head2.jpg");
    zsj::UserData::ptr user1(new zsj::UserData(head, "猪123123123头1", "1231231", "签名1", "备注1"));
    zsj::UserData::ptr user2(new zsj::UserData(head, "狗头1", "1231231", "签名2", "备注2"));
    this->addTreeWidgetChildNode(ui->treeWidgetFriend, rootFriends, user1);
    this->addTreeWidgetChildNode(ui->treeWidgetFriend, rootFriends, user2);

    QPixmap head2(":/test/Z:/default/Pictures/head/head3.jpg");
    zsj::UserData::ptr user3(new zsj::UserData(head2, "陌生人1", "1231231", "签名1", "备注1"));
    zsj::UserData::ptr user4(new zsj::UserData(head2, "陌生人2", "1231231", "签名2", "备注2"));
    this->addTreeWidgetChildNode(ui->treeWidgetFriend, rootStangers, user3);
    this->addTreeWidgetChildNode(ui->treeWidgetFriend, rootStangers, user4);

    for(int i = 0; i < 15; i++)
    {
        QPixmap head3(QString(":/test/Z:/default/Pictures/head/head%1.jpg").arg(i % 5));
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

    qDebug() << "init root";
    QPixmap head1(":/test/Z:/default/Pictures/head/head4.jpg");
    zsj::GroupData::ptr group1(new zsj::GroupData(head1, "富婆交流会所", "123", "群介绍", 0, 0));
    zsj::GroupData::ptr group2(new zsj::GroupData(head1, "2017级计科专业", "123", "群介绍", 0, 0));
    zsj::GroupData::ptr group3(new zsj::GroupData(head1, "星耀2020，信服起航！", "123", "群介绍", 0, 0));
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootTop, group1, "昨天");
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootTop, group2, "7:30");
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootTop, group3, "12-15");

    QPixmap head2(":/test/Z:/default/Pictures/head/head4.jpg");
    zsj::GroupData::ptr group4(new zsj::GroupData(head2, "老污群", "123", "群介绍", 0, 0));
    zsj::GroupData::ptr group5(new zsj::GroupData(head2, "2017级计科专业", "123", "群介绍", 0, 0));
    zsj::GroupData::ptr group6(new zsj::GroupData(head2, "sylar技术群", "123", "群介绍", 0, 0));
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootMy, group4, "11-28");
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootMy, group5, "7:30");
    this->addTreeWidgetChildNode(ui->treeWidgetGroup, rootMy, group6, "16:17");

    QPixmap head3(":/test/Z:/default/Pictures/head/head3.jpg");
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
        QPixmap head(":/test/Z:/default/Pictures/head/head2.jpg");
        MessageItemWidget *messageItem = new MessageItemWidget(head, QString("昵称%1").arg(i), QString("消息%1").arg(i),
                QString("7-%1").arg(i), i % 2, i % 2, ui->listWidgetMessage);
        ui->listWidgetMessage->setItemWidget(item, messageItem);
    }
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
    QPixmap scaled = zsj::scaledPixmap(pixmap, zsj::HeadSize::mainWidth, zsj::HeadSize::mainHeight);
    QPixmap result = zsj::pixmapToRound(scaled, zsj::HeadSize::mainHeight / 2);
    ui->labelHead->setPixmap(result);
}

void MainWidget::setHead(const QString &pixmapPath)
{
    QPixmap origin(pixmapPath);
    setHead(origin);
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

