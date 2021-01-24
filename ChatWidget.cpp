#include "ChatWidget.h"
#include "ui_ChatWidget.h"
#include "ReadQStyleSheet.h"
#include "Util.h"
//#include "Data.h"
#include "GroupData.h"
#include "UserData.h"
#include "ChatObjectItem.h"
#include "StaticIniator.h"

#include <QDebug>
#include <QAction>
#include <QListWidget>
#include <QPoint>
#include <QCursor>
#include <QActionGroup>


ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);
    initObjects();
    initResourceAndForm();
    initSignalsAndSlots();

    initTestData();
}

ChatWidget::~ChatWidget()
{
    delete ui;
}



void ChatWidget::initObjects()
{
    frameless = new zsj::Frameless(this);
    frameless->setPadding(17);


    // 初始化所有菜单
    initMenus();
}

void ChatWidget::initResourceAndForm()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);


    // ://css/chat.css
//    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("D:\\QT\\QtCode\\MySelfQQ_v2\\MySelfQQ_v2\\css\\chat.css"));


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


    // 设置消息发送选项菜单
//    ui->toolButtonSendMenu->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->toolButtonSendMenu->setPopupMode(QToolButton::InstantPopup);
    ui->toolButtonSendMenu->setMenu(sendMenu);



    ui->textEditMessageList->insertHtml("<div style='color:red;width:50px;height:50px;border:1px solid blue;background-color:green;'>hello</div>");

    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("://css/chat.css"));
    qDebug() << "load chat.css";
}

void ChatWidget::initSignalsAndSlots()
{
    connect(ui->toolButtonClose, &QToolButton::clicked, this, &ChatWidget::close);
    qInfo() << "connect toolButtonClose::clicked to ChatWidget::close";

    connect(ui->listWidgetChatObjList, &QListWidget::clicked, this, &ChatWidget::changeChatObject);
    qInfo() << "connect listWidgetChatObjList::clicked to ChatWidget::changeChatObject";

    connect(ui->listWidgetChatObjList, &MyListWidget::sigAddItem, this, &ChatWidget::slotItemAdd);
//    connect(ui->listWidgetChatObjList, &MyListWidget::sigTakeItem, this, &ChatWidget::slotItemTake);

}

void ChatWidget::setChatObjListStyle()
{
    ui->widgetContentLeft->setVisible(false);
}

void ChatWidget::initMenus()
{
    sendMenu = new QMenu();
    zsj::StaticIniator::Instatcne()->initSendMenu(sendMenu, this);

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
        ui->listWidgetChatObjList->addItem(item);
        connect(chatObjsItem, &ChatObjectItem::sigDeleteItem, this, &ChatWidget::slotDeleteChatObject);
    }
}

void ChatWidget::setCurrentData(zsj::Data::ptr data)
{
    if(data)
    {
        this->currentData = data;
        ui->labelCurrentObjName->setText(currentData->getName());
    }
    else
    {
        qCritical() << "paramter data is nullptr";
    }

}

void ChatWidget::slotChooseEnter()
{

}

void ChatWidget::slotChooseCtrlEnter()
{

}

void ChatWidget::changeChatObject(const QModelIndex &index)
{
    if(index == currentIndex)
    {
        return;
    }
    QWidget *widget = ui->listWidgetChatObjList->indexWidget(index);
    if(widget)
    {
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
    else
    {
        qCritical() << "get index widget failed";
    }


}

void ChatWidget::slotDeleteChatObject(QPoint point)
{
    QPoint localPos = ui->listWidgetChatObjList->mapFromGlobal(point);
    QListWidgetItem *item = ui->listWidgetChatObjList->itemAt(localPos);
    if(item)
    {
        ChatObjectItem *chatItem = zsj::WidgetUtil::widgetCast <
                                   QListWidget, QListWidgetItem, ChatObjectItem > (ui->listWidgetChatObjList, item);
        if(chatItem)
        {
            auto deleteItem = ui->listWidgetChatObjList->takeItem(ui->listWidgetChatObjList->row(item));

            if(chatItem->getData() == currentData)
            {
                int lastIndex = ui->listWidgetChatObjList->count() - 1;
                ui->listWidgetChatObjList->setCurrentRow(lastIndex);
                QListWidgetItem *lastItem = ui->listWidgetChatObjList->item(lastIndex);
                ChatObjectItem *chatObj = zsj::WidgetUtil::widgetCast<QListWidget, QListWidgetItem, ChatObjectItem>(ui->listWidgetChatObjList, lastItem);
                this->setCurrentData(chatObj->getData());
            }

            delete deleteItem;
            if(ui->listWidgetChatObjList->count() <= 1)
            {
                setChatObjListStyle();
            }

        }
        else
        {
            qCritical() << "dynamic_cast QWidget to ChatObjectItem failed";
        }
    }
    else
    {
        qCritical() << "that position have not widget";
    }

}

void ChatWidget::slotItemAdd(QListWidgetItem *item)
{
    ui->listWidgetChatObjList->setCurrentItem(item);

    if(!item)
    {
        qDebug() << "item is nullptr";
    }

    ChatObjectItem *chatObj = zsj::WidgetUtil::widgetCast<MyListWidget, QListWidgetItem, ChatObjectItem>
                              (ui->listWidgetChatObjList, item);
    if(chatObj)
    {
        setCurrentData(chatObj->getData());
    }
    else
    {
        qCritical() << "set chat item failed";
    }

}

void ChatWidget::slotItemTake()
{
    qDebug() << "slotItemTake";
    int currentRow = ui->listWidgetChatObjList->currentRow();
    if(currentRow < 0 || currentRow >= ui->listWidgetChatObjList->count())
    {
        ui->listWidgetChatObjList->setCurrentRow(0);
    }
}

