#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "ReadQStyleSheet.h"


#include <QDebug>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    initObjects();
    initResourceAndForm();
    initSignalsAndSlots();
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
    frameless = new Zsj::Frameless(this);
    frameless->setWidget(this);      //设置窗口可移动，可扩展

    systemTray = new Zsj::SystemTray(this);

    systemTray->showSystemTray();
    QPixmap * trayIcon = new QPixmap(":/global/res/global/water-tray.png");
    systemTray->setSystemTrayIcon(trayIcon);
    this->setStyleSheet(Zsj::ReadQStyleSheet::readQss("://css/main.css"));


    //设置窗口阴影
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);   //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(12);     //阴影的模糊半径
    ui->widgetMain->setGraphicsEffect(shadow);

    //选中第一个消息页面
//    switchToMessageWidget();
    switchToLinkmanWidget();

    // 初始化好友列表
    ui->treeWidgetFriend->setIndentation(0);
    initManlinkFriend();
    initManlinkGroup();

}

void MainWidget::initSignalsAndSlots()
{
    connect(ui->toolButtonClose,&QToolButton::clicked,this,&MainWidget::closeWindow);
    qInfo() << "connect QToolButton::clicked to MainWidget::closeWindow";

    connect(ui->toolButtonMin,&QToolButton::clicked,this,&MainWidget::minWindow);
    qInfo() << "connect toolButtonMin::clicked to MainWidget::minWindow";

    connect(systemTray,&Zsj::SystemTray::sigOpenWindow,this,&MainWidget::show);
    qInfo() << "connect systemTray::sigOpenWindow to MainWidget::show";

    connect(ui->pushButtonMessage,&QPushButton::clicked,this,&MainWidget::switchToMessageWidget);
    qInfo() << "connect ui->pushButtonMessage::clicked to MainWidget::switchToMessageWidget";

    connect(ui->pushButtonLinkman,&QPushButton::clicked,this,&MainWidget::switchToLinkmanWidget);
    qInfo() << "connect ui->pushButtonLinkman::clicked to MainWidget::switchToLinkmanWidget";

    connect(ui->pushButtonSpace,&QPushButton::clicked,this,&MainWidget::switchToSpaceWidget);
    qInfo() << "connect ui->pushButtonSpace::clicked to MainWidget::switchToSpaceWidget";

    connect(ui->treeWidgetFriend,&QTreeWidget::itemClicked,this,&MainWidget::treeWidgetItemClick);
    qInfo() << "connect ui->treeWidgetFriend::itemClicked to MainWidget::treeWidgetItemClick";

    connect(ui->treeWidgetFriend,&QTreeWidget::itemExpanded,this,&MainWidget::expanded);
    connect(ui->treeWidgetFriend,&QTreeWidget::itemCollapsed,this,&MainWidget::collasped);
}

void MainWidget::initManlinkFriend()
{
    QTreeWidgetItem * rootFriends = this->addTreeWidgetRootNode(ui->treeWidgetFriend,"我的好友",3,12);
    QTreeWidgetItem * rootStangers = this->addTreeWidgetRootNode(ui->treeWidgetFriend,"陌生人",4,6);
    QPixmap head(":/test/Z:/default/Pictures/head/head2.jpg");
    this->addTreeWidgetChildNode(ui->treeWidgetFriend,rootFriends,head,"猪123123123头1","备注1","签名1");
    this->addTreeWidgetChildNode(ui->treeWidgetFriend,rootFriends,head,"狗头1","备注2","签名2");

    QPixmap head2(":/test/Z:/default/Pictures/head/head3.jpg");
    this->addTreeWidgetChildNode(ui->treeWidgetFriend,rootStangers,head2,"陌生人1","备注1","签名1");
    this->addTreeWidgetChildNode(ui->treeWidgetFriend,rootStangers,head2,"陌生人3","备注2","签名2");
    if(rootFriends == rootStangers){
        qDebug() << "rootFriends == rootStangers";
    }
}

void MainWidget::initManlinkGroup()
{

}

QTreeWidgetItem* MainWidget::addTreeWidgetRootNode(QTreeWidget *treeWidget, LinkmanGroupWidget *group)
{
    if(nullptr != treeWidget && nullptr != group){
        QTreeWidgetItem * rootNode = new QTreeWidgetItem(treeWidget);
        rootNode->setData(0,Qt::UserRole,0);

        treeWidget->addTopLevelItem(rootNode);
        treeWidget->setItemWidget(rootNode,0,group);

        return rootNode;
    }
    else{
        qCritical() << "QTreeWidget Object or LinkmanGroupWidget Object is nullptr!";
        return nullptr;
    }
}

QTreeWidgetItem* MainWidget::addTreeWidgetRootNode(QTreeWidget *treeWidget, const QString &groupName,
                                       int active, int total)
{
    if(nullptr != treeWidget){
        QTreeWidgetItem * rootNode = new QTreeWidgetItem(treeWidget);
        rootNode->setData(0,Qt::UserRole,0);
        QPixmap icon(":/main/res/main/arrow-right.png");
        LinkmanGroupWidget * item = new LinkmanGroupWidget(icon,groupName,active,total,treeWidget);
        treeWidget->addTopLevelItem(rootNode);
        treeWidget->setItemWidget(rootNode,0,item);

        return rootNode;
    }
    else{
        qCritical() << "QTreeWidget object is nullptr!";
        return nullptr;
    }
}

QTreeWidgetItem* MainWidget::addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode,
                                        LinkmanItemWidget *item)
{
    if(nullptr != treeWidget && nullptr != rootNode && nullptr != item ){
        QTreeWidgetItem * child = new QTreeWidgetItem(rootNode);
        child->setData(0,Qt::UserRole,1);
        rootNode->addChild(child);
        treeWidget->setItemWidget(child,0,item);
        return child;
    }
    else{
        qCritical() << "QTreeWidget,QTreeWidgetItem,LinkmanItemWidget Object is nullptr!";
        return nullptr;
    }

}

QTreeWidgetItem* MainWidget::addTreeWidgetChildNode(QTreeWidget *treeWidget, QTreeWidgetItem *rootNode,
                                        const QPixmap &head, const QString &nickname,
                                        const QString &remark, const QString &signature)
{
    if(nullptr != treeWidget && nullptr != rootNode){
        QTreeWidgetItem * child = new QTreeWidgetItem(rootNode);
        child->setData(0,Qt::UserRole,1);
        QString remarkReal = QString("(%1)").arg(remark);
        LinkmanItemWidget * item = new LinkmanItemWidget(head,nickname,remarkReal,signature,treeWidget);
        rootNode->addChild(child);
        treeWidget->setItemWidget(child,0,item);
        return child;
    }
    else{
        qCritical() << "QTreeWidget,QTreeWidgetItem- Object is nullptr!";
        return nullptr;
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

void MainWidget::switchToMessageWidget()
{
    ui->pushButtonMessage->setChecked(true);
    ui->pushButtonLinkman->setChecked(false);
    ui->pushButtonSpace->setChecked(false);
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget::switchToLinkmanWidget()
{
    ui->pushButtonMessage->setChecked(false);
    ui->pushButtonLinkman->setChecked(true);
    ui->pushButtonSpace->setChecked(false);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWidget::switchToSpaceWidget()
{
    ui->pushButtonMessage->setChecked(false);
    ui->pushButtonLinkman->setChecked(false);
    ui->pushButtonSpace->setChecked(true);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWidget::treeWidgetItemClick(QTreeWidgetItem *item, int column)
{
    bool isChild = item->data(0,Qt::UserRole).toBool();
    //判断是否为父节点
    if(false == isChild){
        bool opened = item->isExpanded();
        item->setExpanded(!opened);
        item->setSelected(false);
    }
}

void MainWidget::collasped(QTreeWidgetItem *item)
{
    bool isChild = item->data(0,Qt::UserRole).toBool();
    if(false == isChild){
        QTreeWidget * treeWidget = item->treeWidget();
        if(nullptr != treeWidget){
            QWidget * itemWidget = treeWidget->itemWidget(item,0);
            if(nullptr != itemWidget){
                LinkmanGroupWidget * groupWidget = dynamic_cast<LinkmanGroupWidget*>(itemWidget);
                if(groupWidget != nullptr){
                    groupWidget->setIcon(":/main/res/main/arrow-right.png");
                }
                else{
                    qCritical() << "dynamic_cast failed";
                }
            }
            else{
                qCritical() << "no item widget";
            }
        }
        else{
            qCritical() << "tree widget is null";
        }

    }
}

void MainWidget::expanded(QTreeWidgetItem *item)
{
    bool isChild = item->data(0,Qt::UserRole).toBool();
    if(false == isChild){
        QTreeWidget * treeWidget = item->treeWidget();
        if(nullptr != treeWidget){
            QWidget * itemWidget = treeWidget->itemWidget(item,0);
            if(nullptr != itemWidget){
                LinkmanGroupWidget * groupWidget = dynamic_cast<LinkmanGroupWidget*>(itemWidget);
                if(groupWidget != nullptr){
                    groupWidget->setIcon(":/main/res/main/arrow-down.png");
                }
                else{
                    qCritical() << "dynamic_cast failed";
                }
            }
            else{
                qCritical() << "no item widget";
            }
        }
        else{
            qCritical() << "tree widget is null";
        }

    }
}

