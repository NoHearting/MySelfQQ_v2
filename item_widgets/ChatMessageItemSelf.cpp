#include "ChatMessageItemSelf.h"
#include "ui_ChatMessageItemSelf.h"


#include "main/ChatBubble.h"
#include "utils/Util.h"

ChatMessageItemSelf::ChatMessageItemSelf(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessageItemSelf)
{
    ui->setupUi(this);
    initResourceAndForm();
}

ChatMessageItemSelf::~ChatMessageItemSelf()
{
    delete ui;
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

void ChatMessageItemSelf::initResourceAndForm()
{
    QPixmap ori = chatMessageData->getHead();
    QPixmap localHead = zsj::adjustToHead(ori, 32);
    ui->labelHead->setPixmap(localHead);

    ui->labelMessage->setText(chatMessageData->getMessage());

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
    int pixWidth = fm.horizontalAdvance(message);
    int count = message.size();
    int offset = (abs((pixWidth / count) - font.pixelSize())) * count;
    pixWidth = pixWidth - offset;
    int pixHeight = fm.height();

    int col = (pixWidth / (this->width() - 90)) + 1;
    int width  = col > 1 ? this->width() - 90 : pixWidth + 10;
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

