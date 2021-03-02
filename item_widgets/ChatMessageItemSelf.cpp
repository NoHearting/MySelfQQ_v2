#include "ChatMessageItemSelf.h"
#include "ui_ChatMessageItemSelf.h"


#include "main/ChatBubble.h"
#include "utils/Util.h"

#include <algorithm>

ChatMessageItemSelf::ChatMessageItemSelf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessageItemSelf),
    chatMessageData(nullptr),
    item(nullptr)
{
    ui->setupUi(this);
    initResourceAndForm();
}



ChatMessageItemSelf::ChatMessageItemSelf(zsj::ChatMessageData::ptr data,
        QListWidgetItem *item, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessageItemSelf),
    chatMessageData(data),
    item(item)
{
    ui->setupUi(this);
    initResourceAndForm();
}

ChatMessageItemSelf::~ChatMessageItemSelf()
{
    delete ui;
}

void ChatMessageItemSelf::initResourceAndForm()
{
    QPixmap ori = chatMessageData->getHead();
    QPixmap localHead = zsj::adjustToHead(ori, 32);
    ui->labelHead->setPixmap(localHead);


    ui->labelMessage->setText(chatMessageData->getMessage().replace(
                                  QString::number(zsj::ChatBubble::EmojiInputSize),
                                  QString::number(zsj::ChatBubble::EmojiChatSize)));

    // 清楚所有标签内联样式
    QString clearMessage = zsj::HtmlUtil::RemoveOriginTagStyle(chatMessageData->getMessage(),static_cast<zsj::TagType>(zsj::TAG_ALL));
    chatMessageData->setMessage(clearMessage);


    int fontSize = zsj::ChatBubble::Instance()->getBubbleFontSize();

    this->setStyleSheet(QString("#labelHead{border-radius:16px;border:none;}"
                                "#labelMessage{font-size:%1px;}"
                                "#widget{border-radius:5px;border:1px solid green;}").arg(fontSize)
                       );
}


void ChatMessageItemSelf::adjustWidgetsPosition()
{
    QSize size = calculateMessageWidgetSize();
    int padding = zsj::ChatBubble::Instance()->getBubblePadding();
    ui->labelHead->setGeometry(this->width() - 41, 9, ui->labelHead->width(), ui->labelHead->height());
    ui->widget->setGeometry(QRect(this->width() - size.width() - 2 * padding - 50, 9, size.width() + 2 * padding, size.height() + 2 * padding));
}

QSize ChatMessageItemSelf::calculateMessageWidgetSize()
{
    QFont font = zsj::ChatBubble::Instance()->getBubbleFont();
    QFont newFont(font.family(), font.pixelSize());
    QFontMetrics fm(newFont);
    QString message = chatMessageData->getMessage();
    int pixHeight = fm.height();
    int col = 0;
    int width = getContentMaxWidth(message, this->width(), col, fm);
    int height = pixHeight * col - (pixHeight - font.pixelSize()) * col / 2;
    return QSize(width, height);
}

QSize ChatMessageItemSelf::getWidgetSize()
{
    int padding = zsj::ChatBubble::Instance()->getBubblePadding();
    return QSize(ui->labelMessage->width() + 18 + 2 * padding,
                 ui->labelMessage->height() + 18 + 2 * padding);
}

void ChatMessageItemSelf::resizeEvent(QResizeEvent *event)
{
    adjustWidgetsPosition();
    item->setSizeHint(getWidgetSize());
    QWidget::resizeEvent(event);
}

