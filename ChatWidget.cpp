#include "ChatWidget.h"
#include "ui_ChatWidget.h"
#include "main/ReadQStyleSheet.h"
#include "utils/Util.h"
//#include "Data.h"
#include "main/GroupData.h"
#include "main/UserData.h"
#include "item_widgets/ChatObjectItem.h"
#include "main/StaticIniator.h"
#include "item_widgets/ChatMessageItemObject.h"
#include "item_widgets/ChatMessageItemSelf.h"
#include "item_widgets/ChatMessageImageItemSelf.h"
#include "item_widgets/ChatMessageImageItemObject.h"
#include "screen_shot/ScreenShot.h"
#include "main/ChatBubble.h"
#include "main/CurrentWindow.h"

#include <QDebug>
#include <QAction>
#include <QListWidget>
#include <QPoint>
#include <QCursor>
#include <QActionGroup>
#include <QSize>
#include <QSizePolicy>
#include <QSplitter>
#include <QFileDialog>
#include <QMap>

#include <QDir>
#include <QMimeData>
#include <QClipboard>



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

bool ChatWidget::event(QEvent *event)
{

    // 用于隐藏常用表情窗口
    if(event->type() == QEvent::HoverMove)
    {
        if(emojiHotWidget->isVisible())
        {
            QPoint pos = QCursor::pos();
            // 用户聊天界面和群组界面按钮的位置可能不一样
            QPoint posGlobal = ui->widgetMessageInput->mapToGlobal(ui->toolButtonEmoji->pos());
            QRect rectButton = QRect(posGlobal, ui->toolButtonEmoji->size());
            QPoint posGlobalGroup = ui->widgetMessageInputGroup->mapToGlobal(ui->toolButtonEmojiGroup->pos());
            QRect rectButtonGroup = QRect(posGlobalGroup, ui->toolButtonEmojiGroup->size());
            QRect rectEmojiWindow = emojiHotWidget->geometry();
            if(!rectButton.contains(pos) && !rectButtonGroup.contains(pos) &&
                    !rectEmojiWindow.contains(pos) )
            {
                emojiHotWidget->hide();
            }

        }
    }
    else if(event->type() == QEvent::Resize)
    {
        zsj::CurrentWindow::Instance()->setWindowGeometry(this->geometry());
    }
    else if(event->type() == QEvent::Move)
    {
        zsj::CurrentWindow::Instance()->setWindowGeometry(this->geometry());
    }

    return QWidget::event(event);
}





void ChatWidget::initObjects()
{
    frameless = new zsj::Frameless(this);
    frameless->setPadding(17);


    // 初始化所有菜单
    initMenus();


    emojiWidget = new EmojiWidget(this);
    emojiHotWidget = new EmojiHotWidget(this);
}

void ChatWidget::initResourceAndForm()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
//    setMouseTracking(true);

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

    /// 聊天对象列表
    // 左边聊天对象列表切换对象时
    connect(ui->listWidgetChatObjList, &MyListWidget::itemClicked, this, &ChatWidget::slotChangeChatObject);
    qInfo() << "connect listWidgetChatObjList::clicked to ChatWidget::changeChatObject";
    // 聊天对象列表增加对象时
    connect(ui->listWidgetChatObjList, &MyListWidget::sigAddItem, this, &ChatWidget::slotItemAdd);

    /// 发送消息按钮
    connect(ui->pushButtonSend, &QPushButton::clicked, this, &ChatWidget::slotButtonToSendMessage);
    connect(ui->pushButtonSendGroup, &QPushButton::clicked, this, &ChatWidget::slotButtonToSendMessageGroup);
    qInfo() << "connect pushButtonSend::clicked to ChatWidget::slotButtonToSendMessage";
    connect(ui->pushButtonCloseGroup,&QPushButton::clicked,this,[this](){
        QPixmap head(":/test/res/test/head1.jpg");
        QString content = zsj::HtmlUtil::GetHtmlBodyContent(ui->textEditMessageInputGroup->toHtml());
        QMap<InputMessageType, QStringList> messageMap = parser.parserMessage(content);
        for(auto iter = messageMap.begin(); iter != messageMap.end(); ++iter)
        {
            addMessageItem(ui->listWidgetMessageListGroup, head,
                           iter.key(), iter.value().at(0),false);
        }
        ui->textEditMessageInputGroup->clear();
    });



    // 消息输入框
    connect(ui->textEditMessageInput, &MyTextEdit::sigKeyToSendMsg, this, &ChatWidget::slotKeyToSendMessage);
    connect(ui->textEditMessageInputGroup, &MyTextEdit::sigKeyToSendMsg, this, &ChatWidget::slotKeyToSendMessageGroup);
    qInfo() << "connect textEditMessageInput::sigKeyToSendMsg to ChatWidget::slotKeyToSendMessage";

    // 全屏按钮
    connect(ui->toolButtonFullScreen, &QToolButton::clicked, this, &ChatWidget::slotMaxShowMessageList);
    connect(ui->toolButtonFullScreenGroup, &QToolButton::clicked, this, &ChatWidget::slotMaxShowMessageListGroup);

    // 截屏按钮
    connect(ui->toolButtonScreenShot, &QToolButton::clicked, this, &ChatWidget::slotScreenShot);
    connect(ui->toolButtonScreenShotGroup, &QToolButton::clicked, this, &ChatWidget::slotScreenShot);
    qInfo() << "连接截屏的信号和槽";


    /// 截屏按钮
    // 当鼠标在截屏按钮上悬空
    connect(ui->toolButtonEmoji, &MyToolButton::sigEnter, this, [this]()
    {
        QPoint pos = ui->widgetMessageInput->mapToGlobal(ui->toolButtonEmoji->pos());
        emojiHotWidget->adjustPosition(pos);
        emojiHotWidget->show(zsj::global::UiType::USER);
    });
    connect(ui->toolButtonEmojiGroup, &MyToolButton::sigEnter, this, [this]()
    {
        qDebug() << "group enter";
        QPoint pos = ui->widgetMessageInputGroup->mapToGlobal(ui->toolButtonEmojiGroup->pos());
        emojiHotWidget->adjustPosition(pos);
        emojiHotWidget->show(zsj::global::UiType::GROUP);
    });

    // 松开表情按钮
    connect(ui->toolButtonEmoji, &QToolButton::released, this, [this]()
    {
        if(ui->toolButtonEmoji->isChecked())
        {

            QPoint pos = ui->widgetMessageInput->mapToGlobal(ui->toolButtonEmoji->pos());
            emojiWidget->adjustPosition(pos);
            emojiWidget->show(zsj::global::UiType::USER);
        }
    });
    connect(ui->toolButtonEmojiGroup, &QToolButton::released, this, [this]()
    {
        if(ui->toolButtonEmojiGroup->isChecked())
        {

            QPoint pos = ui->widgetMessageInputGroup->mapToGlobal(ui->toolButtonEmojiGroup->pos());
            emojiWidget->adjustPosition(pos);
            emojiWidget->show(zsj::global::UiType::GROUP);
        }
    });

    // 表情窗口关闭
    connect(emojiWidget, &EmojiWidget::sigWindowClose, this, [this]()
    {
        ui->toolButtonEmoji->setChecked(false);
        ui->toolButtonEmojiGroup->setChecked(false);
    });

    // 选择表情
    connect(emojiWidget, &EmojiWidget::sigChooseEmoji, this, &ChatWidget::slotChooseEmoji);
    connect(emojiHotWidget, &EmojiHotWidget::sigChooseEmoji, this, &ChatWidget::slotChooseEmoji);


    // 选择图片
    connect(ui->toolButtonImage, &QToolButton::clicked, this, &ChatWidget::slotChooseImageFile);
    connect(ui->toolButtonImageGroup, &QToolButton::clicked, this, &ChatWidget::slotChooseImageFileGroup);
}

void ChatWidget::setChatObjListStyle()
{
    ui->widgetContentLeft->setVisible(false);
}

void ChatWidget::initMenus()
{
    sendMenu = new QMenu();
    zsj::StaticIniator::Instance()->initSendMenu(sendMenu, this);

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

void ChatWidget::addMessageItem(QListWidget *listWidget, QPixmap &head,
                                const QString &message, bool isSelf)
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

void ChatWidget::addMessageItem(QListWidget *listWidget, QPixmap &head,
                                ChatWidget::InputMessageType inputType,
                                const QString &message, bool isSelf)
{
#define SWITCH(name) \
    switch(inputType){ \
        case InputMessageType::IMAGE: \
            data.reset(new zsj::ChatMessageData(message,head)); \
            widget = new ChatMessageImageItem##name(data, item, listWidget); \
            break; \
        case InputMessageType::EMOJI_TEXT: \
            if(parser.contentJudgeEmpty(message)){ \
                data->setHasEmoji(true); \
                widget = new ChatMessageItem##name(data, item, listWidget); \
                break; \
            } \
        case InputMessageType::PLAIN_TEXT: \
            if(parser.contentJudgeEmpty(message)){ \
                widget = new ChatMessageItem##name(data, item, listWidget); \
                break; \
            }\
    }

    QListWidgetItem *item = new QListWidgetItem(listWidget);
    listWidget->addItem(item);
    zsj::ChatMessageData::ptr data(new zsj::ChatMessageData(head, message));
    QWidget *widget = nullptr;
    if(isSelf)
    {
        SWITCH(Self);
    }
    else
    {
        SWITCH(Object);
    }
    listWidget->setItemWidget(item, widget);

    // 滚动到最底部
    listWidget->scrollToBottom();

#undef SWITCH
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
    QString content = zsj::HtmlUtil::GetHtmlBodyContent(ui->textEditMessageInput->toHtml());
    QMap<InputMessageType, QStringList> messageMap = parser.parserMessage(content);
    for(auto iter = messageMap.begin(); iter != messageMap.end(); ++iter)
    {
        addMessageItem(ui->listWidgetMessageList, head, iter.key(), iter.value().at(0));
    }
    ui->textEditMessageInput->clear();

}

void ChatWidget::slotButtonToSendMessageGroup()
{
    QPixmap head(":/test/res/test/head1.jpg");
    QString content = zsj::HtmlUtil::GetHtmlBodyContent(ui->textEditMessageInputGroup->toHtml());
    qDebug() << "**************" << content;
    QMap<InputMessageType, QStringList> messageMap = parser.parserMessage(content);
    for(auto iter = messageMap.begin(); iter != messageMap.end(); ++iter)
    {
        addMessageItem(ui->listWidgetMessageListGroup, head, iter.key(), iter.value().at(0));
    }
    ui->textEditMessageInputGroup->clear();
}


void ChatWidget::slotKeyToSendMessage(const QString &msg)
{
    QPixmap head(":/test/res/test/head4.jpg");

    QMap<InputMessageType, QStringList> messageMap = parser.parserMessage(msg);
    for(auto iter = messageMap.begin(); iter != messageMap.end(); ++iter)
    {
        addMessageItem(ui->listWidgetMessageList, head, iter.key(), iter.value().at(0));
    }
    ui->textEditMessageInput->clear();

}

void ChatWidget::slotKeyToSendMessageGroup(const QString &msg)
{
    QPixmap head(":/test/res/test/head1.jpg");
    QMap<InputMessageType, QStringList> messageMap = parser.parserMessage(msg);
    for(auto iter = messageMap.begin(); iter != messageMap.end(); ++iter)
    {
        addMessageItem(ui->listWidgetMessageListGroup, head, iter.key(), iter.value().at(0));
    }
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

void ChatWidget::slotChooseEmoji(zsj::global::UiType type, const QString &emojiPath)
{
    emojiHotWidget->recordHotEmoji(emojiPath);
    QString src = zsj::Util::PackageImageHtml(emojiPath, zsj::ChatBubble::EmojiInputSize,
                  zsj::ChatBubble::EmojiInputSize);
    if(type == zsj::global::UiType::USER)
    {
        ui->textEditMessageInput->insertHtml(src);
    }
    else
    {
        ui->textEditMessageInputGroup->insertHtml(src);
    }
    qDebug() << "chooseEmoji: " << src;
}

void ChatWidget::slotScreenShot()
{
    zsj::ScreenShot::Instance();
}

void ChatWidget::slotShowEmojiWidget()
{
    if(ui->toolButtonEmoji->isChecked())
    {

        QPoint pos = ui->widgetMessageInput->mapToGlobal(ui->toolButtonEmoji->pos());
        emojiWidget->adjustPosition(pos);
        emojiWidget->show(zsj::global::UiType::USER);
    }
}

void ChatWidget::slotChooseImageFile()
{
    QString imageFile = QFileDialog::getOpenFileName(this, "打开", QDir::currentPath(), "图片文件(*.jpg *.gif *.png)");
    qDebug() << imageFile;
    if(!imageFile.isEmpty())
    {
        QPixmap pix(imageFile);
        QSize contentSize = zsj::Util::ScaledImageSize(pix.size());
        QString imgUrl = zsj::Util::PackageImageHtml(imageFile, contentSize.width(), contentSize.height());
        ui->textEditMessageInput->insertHtml(imgUrl);
    }
    else
    {
        qCritical() << "选择图片失败";
    }
}

void ChatWidget::slotChooseImageFileGroup()
{
    QString imageFile = QFileDialog::getOpenFileName(this, "打开", QDir::currentPath(), "图片文件(*.jpg *.gif *.png)");
    qDebug() << imageFile;
    if(!imageFile.isEmpty())
    {
        QPixmap pix(imageFile);
        QSize contentSize = zsj::Util::ScaledImageSize(pix.size());
        QString imgUrl = zsj::Util::PackageImageHtml(imageFile, contentSize.width(), contentSize.height());
        ui->textEditMessageInputGroup->insertHtml(imgUrl);
    }
    else
    {
        qCritical() << "选择图片失败";
    }

}


QMap<ChatWidget::InputMessageType, QStringList> ChatWidget::MessageParser::parserMessage(QString originmessage)
{
    //去掉第一个QTextedit自带的换行\n
    int begin = originmessage.indexOf("\n");
    qDebug() << begin;
    originmessage = originmessage.remove(begin, 1);
    qDebug() << originmessage;

    QMap<ChatWidget::InputMessageType, QStringList> messageMap;
    bool hasEmoji = false;
    int index = 0;
    do
    {
        int begin = originmessage.indexOf("<img", index);
        if(begin == -1)
        {
            break;
        }
        int end = originmessage.indexOf(">", begin + 1);
        if(-1 == end)
        {
            break;
        }
        QString tag = originmessage.mid(begin, end - begin + 1);
        if(!tag.contains("emoji"))
        {
            originmessage.replace(tag, "");
            messageMap[InputMessageType::IMAGE].append(tag);
        }
        else
        {
            hasEmoji = true;
        }
        index = end;
    }
    while(index < originmessage.size());

    if(hasEmoji)
    {
        messageMap[InputMessageType::EMOJI_TEXT].append(originmessage);
    }
    else
    {
        messageMap[InputMessageType::PLAIN_TEXT].append(originmessage);
    }

    return messageMap;
}

bool ChatWidget::MessageParser::contentJudgeEmpty(const QString &content)
{
    QString newContent = zsj::HtmlUtil::RemoveOriginTagStyle(content, (zsj::TagType)(zsj::TAG_BODY | zsj::TAG_SPAN | zsj::TAG_P));
    if(newContent == "<body></body>" || newContent == "<p></p>" ||
            newContent == "<span></span>" ||
            newContent == "<p><span></span><p>" ||
            newContent == "<body><p></p></body>" ||
            newContent == "<body><span></span></body>" ||
            newContent == "<body><p><span></span></p></body>")
    {
        return false;
    }
    else
    {
        return true;
    }
}
