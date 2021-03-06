#include "ChatObjectItem.h"
#include "ui_ChatObjectItem.h"

#include "utils/Util.h"

#include <QSize>
#include <QStringList>
#include <QDebug>

ChatObjectItem::ChatObjectItem(zsj::Data::ptr data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatObjectItem),
    data(data)
{
    ui->setupUi(this);

    init();
}

ChatObjectItem::~ChatObjectItem()
{
    delete ui;
}

void ChatObjectItem::resizeEvent(QResizeEvent *e)
{
//    adjustLabelPostion();
    if(this->width() < 188){
        ui->labelDate->hide();
        ui->toolButtonClose->hide();
        if(this->width() <= 100){
            ui->labelNickname->hide();
            ui->labelMessage->hide();
        }
        else{
            ui->labelNickname->show();
            ui->labelMessage->show();
        }
    }
    else{
        ui->labelDate->show();
        ui->labelNickname->show();
        ui->labelMessage->show();
        adjustLabelPostion();
    }

    QWidget::resizeEvent(e);
}

void ChatObjectItem::enterEvent(QEvent *event)
{
    ui->toolButtonClose->show();

    QWidget::enterEvent(event);
}

void ChatObjectItem::leaveEvent(QEvent *event)
{
    ui->toolButtonClose->hide();

    QWidget::leaveEvent(event);
}

void ChatObjectItem::init()
{
    // 设置数据
    QPixmap pix = data->getHead();
    ui->labelHead->setPixmap(zsj::adjustToHead(pix,40));
    ui->labelNickname->setText(data->getName());
    ui->labelMessage->setText("messages....");
    ui->labelDate->setText(zsj::GetCurrentDateTime());

    ui->toolButtonClose->hide();
    adjustLabelText();

    adjustLabelPostion();

    initStyleSheet();

    connect(ui->toolButtonClose,&QToolButton::clicked,this,&ChatObjectItem::slotDeleteItem);
}

void ChatObjectItem::adjustLabelText()
{
    ui->labelDate->adjustSize();
    ui->labelMessage->adjustSize();
    ui->labelNickname->adjustSize();
}

void ChatObjectItem::adjustLabelPostion()
{
    QSize size = this->size();
    ui->labelDate->setGeometry(size.width() - ui->labelDate->width() - 12, ui->labelDate->pos().y(),
                               ui->labelDate->width(), ui->labelDate->height());
    ui->toolButtonClose->setGeometry(size.width() - ui->toolButtonClose->width() - 12, ui->toolButtonClose->pos().y(),
                                     ui->toolButtonClose->width(), ui->toolButtonClose->height());
}

void ChatObjectItem::initStyleSheet()
{
    QStringList list;
    list.append("#labelHead{border-radius:20px;border:none;}");
    list.append("#toolButtonClose{background:url(\":/chat/res/chat/delete-chat-item.png\");border:none;}");
    list.append("#toolButtonClose:hover{background:url(\":/chat/res/chat/delete-chat-item-hover.png\");}");
    list.append("#labelDate,#labelMessage{color:gray;}");
    QString qss = list.join("\n");
    this->setStyleSheet(qss);
}

void ChatObjectItem::slotDeleteItem()
{
    QPoint globalPos = this->mapToGlobal(ui->toolButtonClose->pos());
    emit sigDeleteItem(globalPos);
}

zsj::Data::ptr ChatObjectItem::getData() const
{
    return data;
}

QRect ChatObjectItem::getDeleteButtonPosition() const
{
    return ui->toolButtonClose->geometry();
}

void ChatObjectItem::setDateTime(const QDateTime &dateTime)
{
    ui->labelDate->setText(dateTime.toString("MM-dd hh:mm"));
    ui->labelDate->adjustSize();
}

void ChatObjectItem::setMessage(const QString &message)
{
    QString result = zsj::HtmlUtil::RemoveOriginTagStyle(message,zsj::TagType::TAG_ALL);
    ui->labelMessage->setText(result);
    ui->labelMessage->adjustSize();
}

