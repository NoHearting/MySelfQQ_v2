#include "ChatWidget.h"
#include "ui_ChatWidget.h"
#include "ReadQStyleSheet.h"
#include "Util.h"
//#include "Data.h"
#include "GroupData.h"
#include "UserData.h"
#include "ChatObjectItem.h"

#include <QDebug>
#include <QAction>
#include <QListWidget>


ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    initObjects();
    initResourceAndForm();
    initSignalsAndSlots();
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

void ChatWidget::paintEvent(QPaintEvent *event)
{
    qDebug() << "paint event";
    QWidget::paintEvent(event);
}

void ChatWidget::initObjects()
{
    frameless = new zsj::Frameless(this);
    frameless->setPadding(17);
}

void ChatWidget::initResourceAndForm()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);


    // ://css/chat.css
//    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("D:\\QT\\QtCode\\MySelfQQ_v2\\MySelfQQ_v2\\css\\chat.css"));
    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("://css/chat.css"));
    qDebug() << "load chat.css";
    zsj::WidgetUtil::setWidgetBoxShadow(ui->widgetBody);


    QRect localGeometry = ui->widgetContentLeft->geometry();
    localGeometry.setWidth(200);
    ui->widgetContentLeft->setGeometry(localGeometry);
    localGeometry = ui->widgetMessageList->geometry();
    localGeometry.setHeight(600);
    ui->widgetMessageList->setGeometry(localGeometry);
//    qDebug() << localGeometry;

    // 初始化搜索框的搜索图标
    QAction *action = new QAction(ui->lineEditSearch);
    action->setIcon(QIcon(":/main/res/main/search.png"));
    ui->lineEditSearch->addAction(action, QLineEdit::LeadingPosition);

    initTestData();

}

void ChatWidget::initSignalsAndSlots()
{
    connect(ui->toolButtonClose, &QToolButton::clicked, this, &ChatWidget::close);
    qInfo() << "connect toolButtonClose::clicked to ChatWidget::close";

    connect(ui->listWidgetChatObjList, &QListWidget::clicked, this, &ChatWidget::changeChatObject);
    qInfo() << "connect listWidgetChatObjList::clicked to ChatWidget::changeChatObject";

//    connect(ui->listWidgetChatObjList,&QListWidget::)
}

void ChatWidget::initTestData()
{
    initTestChatObjs();
}

void ChatWidget::initTestChatObjs()
{
    int count = 15;
    for(int i = 0; i < count; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidgetChatObjList);
        ui->listWidgetChatObjList->addItem(item);
        item->setSizeHint(QSize(ui->widgetContentLeftBottom->width(), 60));
        zsj::Data::ptr data = nullptr;
        QPixmap head(QString(":/test/res/test/head%1.jpg").arg(i % 5));
        if(i % 2)
        {
            data.reset(new zsj::UserData(head, QString("userName-%1").arg(i), "1111", "签名", "备注"));
        }
        else
        {
            data.reset(new zsj::GroupData(head, QString("groupName-%1").arg(i), "222", "群介绍", 10, 100));
        }
        ChatObjectItem *chatObjsItem = new ChatObjectItem(data, ui->listWidgetChatObjList);
        ui->listWidgetChatObjList->setItemWidget(item, chatObjsItem);
    }
}

void ChatWidget::changeChatObject(const QModelIndex &index)
{
    if(index == currentIndex){
        return;
    }
    QWidget *widget = ui->listWidgetChatObjList->indexWidget(index);
    ChatObjectItem *objItem = dynamic_cast<ChatObjectItem *>(widget);
    if(objItem != nullptr)
    {
        currentData = objItem->getData();
        switch(currentData->getDataType())
        {
            case zsj::global::DataType::GROUP_DATA:
                ui->stackedWidgetMain->setCurrentIndex(1);
                qDebug() << "更改到群组的界面";
                break;
            case zsj::global::DataType::USER_DATA:
                ui->stackedWidgetMain->setCurrentIndex(0);
                qDebug() << "执行用户类型的逻辑";
                break;
            case zsj::global::DataType::SYSTEM_DATA:
                qDebug() << "执行系统类型的逻辑";
                break;
        }
        ui->labelCurrentObjName->setText(currentData->getName());
    }
    else
    {
        qCritical() << "list item convert to ChatObjectItem failed";
    }

}

#ifdef Q_OS_LINUX

// 含有一个移动bug
// 当打开比如下拉框、菜单的东西时，点击桌面（不点击下拉框和菜单），此时移动鼠标到窗口，
// 窗口会突然非法移动
void ChatWidget::mouseMoveEvent(QMouseEvent *e)
{
    QPoint afterMovePos = e->globalPos();
    if(offset.x() != 0 && offset.y() != 0)
    {
        QPoint moveDis = afterMovePos - offset;
        move(moveDis);
        qDebug() << "move widget";
    }
}

/*
    鼠标按下事件，按下就获取当前鼠标坐标并计算出当前坐标和窗口左上角的偏移量offset
*/
void ChatWidget::mousePressEvent(QMouseEvent *e)
{
    QPoint topLeft = ui->widgetBody->mapToGlobal(ui->widgetBody->pos()) - QPoint(0, 130);
    QRect realGeometry(topLeft, QSize(ui->widgetBody->size())); // 当前窗口的真实位置大小
    QPoint cursorPos = e->globalPos();              //当前鼠标的全局位置
    if(realGeometry.contains(cursorPos))
    {
        QPoint geometryTopLeft = this->geometry().topLeft();    //当前鼠标点击窗口的左上角坐标
        offset = cursorPos - geometryTopLeft;
    }
}

/*
    鼠标放开事件，当鼠标放开时，将偏移量offset初始化为0
*/
void ChatWidget::mouseReleaseEvent(QMouseEvent *)
{
    offset = QPoint(0, 0);
}
#endif
