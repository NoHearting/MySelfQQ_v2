#include "ChatMessageItemObject.h"
#include "ui_ChatMessageItemObject.h"

#include "utils/Util.h"
#include "main/ChatBubble.h"

ChatMessageItemObject::ChatMessageItemObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessageItemObject),
    item(nullptr),
    chatMessageData(nullptr)

{
    ui->setupUi(this);
    initResourceAndForm();
}

ChatMessageItemObject::ChatMessageItemObject(zsj::ChatMessageData::ptr data,
        QListWidgetItem *item, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessageItemObject),
    item(item),
    chatMessageData(data)

{
    ui->setupUi(this);
    initResourceAndForm();
}


ChatMessageItemObject::~ChatMessageItemObject()
{
    delete ui;
}

void ChatMessageItemObject::initResourceAndForm()
{
    QPixmap ori = chatMessageData->getHead();
    QPixmap localHead = zsj::adjustToHead(ori, 32);
    ui->labelHead->setPixmap(localHead);

    ui->labelMessage->setText(chatMessageData->getMessage()
                              .replace(
                                  QString::number(zsj::ChatBubble::EmojiInputSize),
                                  QString::number(zsj::ChatBubble::EmojiChatSize)));

    int fontSize = zsj::ChatBubble::Instance()->getBubbleFontSize();

    this->setStyleSheet(QString("#labelHead{border-radius:16px;border:none;}"
                                "#labelMessage{font-size:%1px;}"
                                "#widget{border-radius:5px;border:1px solid green;}").arg(fontSize)
                       );
}

void ChatMessageItemObject::adjustWidgetsPosition()
{
    QSize size = calculateMessageWidgetSize();
    int padding = zsj::ChatBubble::Instance()->getBubblePadding();
    ui->widget->setGeometry(QRect(50, 9, size.width() + 2 * padding, size.height() + 2 * padding));
}

QSize ChatMessageItemObject::calculateMessageWidgetSize()
{
    QFont font = zsj::ChatBubble::Instance()->getBubbleFont();
    QFont newFont(font.family(), font.pixelSize());
    QFontMetrics fm(newFont);
    QString message = chatMessageData->getMessage();

    // 去掉html标签中可能存在的内联样式。因为需要通过html来计算气泡的自适应宽度
    message = zsj::HtmlUtil::RemoveOriginTagStyle(message, static_cast<zsj::TagType>(zsj::TAG_P | zsj::TAG_BODY | zsj::TAG_SPAN));
    int pixHeight = fm.height();
    int col = 0;
    int width = getContentMaxWidth(message, this->width(), col, fm);
    int height = pixHeight * col - (pixHeight - font.pixelSize()) * col / 2;

    return QSize(width, height);
}

QSize ChatMessageItemObject::getWidgetSize()
{
    int padding = zsj::ChatBubble::Instance()->getBubblePadding();
    return QSize(ui->labelMessage->width() + 18 + 2 * padding,
                 ui->labelMessage->height() + 18 + 2 * padding);
}

void ChatMessageItemObject::resizeEvent(QResizeEvent *event)
{
    adjustWidgetsPosition();
    item->setSizeHint(getWidgetSize());
    QWidget::resizeEvent(event);
}


