#include "ChatWidget.h"
#include "ui_ChatWidget.h"
#include "ReadQStyleSheet.h"
#include "Util.h"
//#include "Data.h"
#include "GroupData.h"
#include "UserData.h"
#include "ChatObjectItem.h"
#include "StaticIniator.h"
#include "ChatMessageItemObject.h"
#include "ChatMessageItemSelf.h"

#include <QDebug>
#include <QAction>
#include <QListWidget>
#include <QPoint>
#include <QCursor>
#include <QActionGroup>
#include <QSize>
#include <QSizePolicy>
#include <QSplitter>


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

void ChatWidget::showMaximizedWindow()
{
    windowGeometry = this->geometry();

//    QSize desktopSize = zsj::SystemUtil::getDesktopSize();
    QRect desktopGeometry = zsj::SystemUtil::getAvailableGeometry();

    int padding = zsj::global::TopLayoutPadding;
    this->setGeometry(desktopGeometry.x() - padding, desktopGeometry.y() - padding,
                      desktopGeometry.width() + 2 * padding, desktopGeometry.height() + 2 * padding);
}

void ChatWidget::showNormalWindow()
{
    this->setGeometry(windowGeometry);
}

void ChatWidget::resizeEvent(QResizeEvent *event)
{
    // 当窗口变化的时候，如果输入框为全屏状态，则应该适应窗口的变化
    if(ui->widgetMessageListBody->isHidden())
    {
        ui->splitterContent->moveSplitter(ui->widgetMessageListTools->height(), 1);
    }
    if(ui->widgetMessageListBodyGroup->isHidden())
    {

        ui->splitterContentGroup->moveSplitter(ui->widgetMessageListToolsGroup->height(), 1);
    }
    QWidget::resizeEvent(event);
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
    ui->toolButtonSendMenu->setPopupMode(QToolButton::InstantPopup);
    ui->toolButtonSendMenu->setMenu(sendMenu);
    ui->toolButtonSendMenuGroup->setPopupMode(QToolButton::InstantPopup);
    ui->toolButtonSendMenuGroup->setMenu(sendMenu);

    // 滚动条设置按照像素滚动
    ui->listWidgetMessageList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);



//    ui->textEditMessageList->insertHtml("<div style='color:red;width:50px;height:50px;border:1px solid blue;background-color:green;'>hello</div>");

    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("://css/chat.css"));
    qDebug() << "load chat.css";
}

void ChatWidget::initSignalsAndSlots()
{
    connect(ui->toolButtonClose, &QToolButton::clicked, this, &ChatWidget::close);
    qInfo() << "connect toolButtonClose::clicked to ChatWidget::close";

    connect(ui->toolButtoMin, &QToolButton::clicked, this, &ChatWidget::showMinimized);
    qInfo() << "connect toolButtoMin::clicked to ChatWidget::showMinimized";

    connect(ui->toolButtonMax, &QToolButton::clicked, this, &ChatWidget::slotShowMaxWindow);
    qInfo() << "connect toolButtonMax::clicked to ChatWidget::showMaximized";

    connect(ui->listWidgetChatObjList, &MyListWidget::itemClicked, this, &ChatWidget::slotChangeChatObject);
    qInfo() << "connect listWidgetChatObjList::clicked to ChatWidget::changeChatObject";

    connect(ui->listWidgetChatObjList, &MyListWidget::sigAddItem, this, &ChatWidget::slotItemAdd);
//    connect(ui->listWidgetChatObjList, &MyListWidget::sigTakeItem, this, &ChatWidget::slotItemTake);


    connect(ui->pushButtonSend, &QPushButton::clicked, this, &ChatWidget::slotButtonToSendMessage);
    connect(ui->pushButtonSendGroup, &QPushButton::clicked, this, &ChatWidget::slotButtonToSendMessageGroup);
    qInfo() << "connect pushButtonSend::clicked to ChatWidget::slotButtonToSendMessage";

    connect(ui->textEditMessageInput, &MyTextEdit::sigKeyToSendMsg, this, &ChatWidget::slotKeyToSendMessage);
    connect(ui->textEditMessageInputGroup, &MyTextEdit::sigKeyToSendMsg, this, &ChatWidget::slotKeyToSendMessageGroup);
    qInfo() << "connect textEditMessageInput::sigKeyToSendMsg to ChatWidget::slotKeyToSendMessage";

    connect(ui->toolButtonFullScreen, &QToolButton::clicked, this, &ChatWidget::slotMaxShowMessageList);
    connect(ui->toolButtonFullScreenGroup, &QToolButton::clicked, this, &ChatWidget::slotMaxShowMessageListGroup);


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
    initTestMessageList();
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

void ChatWidget::initTestMessageList()
{
    QString msg1 = "阿斯达记录卡开发及时三等奖阿斯达垃圾啊施蒂利克";
    QString msg2 = "asldkjasjdlkasjdlakjflkajsfl遇kajskfajlksfja遇lsfja遇lksjfl遇akfjlkajfl遇kajsflk遇"
                   "asldkjasjdlkasjdlakjflk遇ajsflk遇ajskf遇a遇jlks遇fjalsfj遇alksjflak遇fjlkajflkajsflk遇";

    QString msg3 = "第一类人，生下来就又一种使命感，在成年之前的各种经历，尤其是不幸的遭遇，都是为了强化这个使命，所谓“天降大任于斯人也，必先苦其心志，劳其筋骨”。究其一生，都在为这个使命而奋斗，什么功名利禄，什么困难屈辱，在他的眼里都是过眼烟云。这个使命可以非常具体，也可以非常抽象，但一生专注于这一件事，做到极致； "
                   "第二类人，成年之前，可谓一帆风顺，沿着社会和家庭安排好的线路，系统的学得一身本领和知识。他人生的目的不是非常明确，但学习和成长是其生活中很重要的部分，他比较在乎自己的名声和名节，有些清高和矜持，如同出世的贤人。他的很多目标是阶段性的，实现了之后，就有一段闲云野鹤的日子，总之不想被束缚；";

    for(int i = 0; i < 7; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidgetMessageList);
//        item->setSizeHint(QSize(ui->listWidget->width(),100));
        ui->listWidgetMessageList->addItem(item);


        QPixmap pic("Z:\\default\\Pictures\\head\\head0.jpg");
        QString msg;
        switch(i % 3 + 1)
        {
            case 1:
                msg = msg1;
                break;
            case 2:
                msg = msg2;
                break;
            case 3:
                msg = msg3;
                break;
        }
        zsj::ChatMessageData::ptr data(new zsj::ChatMessageData(pic, msg));
        if(i % 2)
        {
            auto *cmio = new ChatMessageItemObject(data, item, ui->listWidgetMessageList);
            ui->listWidgetMessageList->setItemWidget(item, cmio);
        }
        else
        {
            auto *cmio = new ChatMessageItemSelf(data, item, ui->listWidgetMessageList);
            ui->listWidgetMessageList->setItemWidget(item, cmio);
        }

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

void ChatWidget::addMessageItem(QListWidget *listWidget, QPixmap &head, const QString &message, bool isSelf)
{
    QListWidgetItem *item = new QListWidgetItem(listWidget);
    listWidget->addItem(item);
    zsj::ChatMessageData::ptr data(new zsj::ChatMessageData(head, message));
    QWidget *widget = nullptr;
    if(isSelf)
    {
        widget = new ChatMessageItemSelf(data, item, listWidget);
    }
    else
    {
        widget = new ChatMessageItemObject(data, item, listWidget);
    }
    listWidget->setItemWidget(item, widget);

    // 滚动到最底部
    listWidget->scrollToBottom();

}



void ChatWidget::slotChooseEnter()
{
    ui->textEditMessageInput->setEnterSendMsg();
    ui->textEditMessageInputGroup->setEnterSendMsg();
}

void ChatWidget::slotChooseCtrlEnter()
{
    ui->textEditMessageInput->setCtrlEnterSendMsg();
    ui->textEditMessageInputGroup->setCtrlEnterSendMsg();
}

void ChatWidget::slotShowMaxWindow()
{
    static bool isMax = false;
    if(!isMax)
    {
        this->showMaximizedWindow();
        isMax = !isMax;
    }
    else
    {
        this->showNormalWindow();
        isMax = !isMax;
    }
}

void ChatWidget::slotChangeChatObject(QListWidgetItem *item)
{
    if(currentItem == item)
    {
        return;
    }

    ChatObjectItem *chatObj = zsj::WidgetUtil::widgetCast<MyListWidget, QListWidgetItem, ChatObjectItem>
                              (ui->listWidgetChatObjList, item);
    if(chatObj)
    {
        currentItem = item;
        setCurrentData(chatObj->getData());
        switchChatObj();
    }
    else
    {
        qCritical() << "change chat object failed!";
    }
}

void ChatWidget::switchChatObj()
{
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

    // 设置数据
    // 目前只有一个简单的数据
    ui->labelCurrentObjName->setText(currentData->getName());
}

void ChatWidget::changeMessageInput()
{
    static bool isChecked = false;
    static int maxHeightInput = ui->widgetMessageInput->maximumHeight();
    if(isChecked)
    {
        ui->widgetMessageListBody->setVisible(true);
        ui->widgetMessageInput->setMaximumHeight(maxHeightInput);
        ui->widgetMessageListBodyGroup->setVisible(true);
        ui->widgetMessageInputGroup->setMaximumHeight(maxHeightInput);
        isChecked = false;
    }
    else
    {
        ui->widgetMessageInput->setMaximumHeight(9999);
        ui->widgetMessageListBody->setVisible(false);

        ui->splitterContent->moveSplitter(ui->widgetMessageListTools->height(), 1);

        ui->widgetMessageInputGroup->setMaximumHeight(9999);
        ui->widgetMessageListBodyGroup->setVisible(false);

        ui->splitterContentGroup->moveSplitter(0, 1);

        isChecked = true;
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
                switchChatObj();
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

    ChatObjectItem *chatObj = zsj::WidgetUtil::widgetCast<MyListWidget, QListWidgetItem, ChatObjectItem>
                              (ui->listWidgetChatObjList, item);
    if(chatObj)
    {
        currentItem = item;
        setCurrentData(chatObj->getData());
        switchChatObj();
    }
    else
    {
        qCritical() << "set chat item failed";
    }

}


void ChatWidget::slotButtonToSendMessage()
{
    QPixmap head(":/test/res/test/head4.jpg");
    QString msg = ui->textEditMessageInput->toPlainText();
    addMessageItem(ui->listWidgetMessageList, head, msg);
    ui->textEditMessageInput->clear();

}

void ChatWidget::slotButtonToSendMessageGroup()
{
    QPixmap head(":/test/res/test/head1.jpg");
    QString msg = ui->textEditMessageInputGroup->toPlainText();
    addMessageItem(ui->listWidgetMessageListGroup, head, msg);
    ui->textEditMessageInputGroup->clear();
}


void ChatWidget::slotKeyToSendMessage(const QString &msg)
{
    QPixmap head(":/test/res/test/head4.jpg");
    addMessageItem(ui->listWidgetMessageList, head, msg);
    ui->textEditMessageInput->clear();

}

void ChatWidget::slotKeyToSendMessageGroup(const QString &msg)
{
    QPixmap head(":/test/res/test/head1.jpg");
    addMessageItem(ui->listWidgetMessageListGroup, head, msg);
    ui->textEditMessageInputGroup->clear();
}

void ChatWidget::slotMaxShowMessageList()
{
    changeMessageInput();
    ui->toolButtonFullScreenGroup->setChecked(!ui->toolButtonFullScreenGroup->isChecked());
}

void ChatWidget::slotMaxShowMessageListGroup()
{
    changeMessageInput();
    ui->toolButtonFullScreen->setChecked(!ui->toolButtonFullScreen->isChecked());
}

