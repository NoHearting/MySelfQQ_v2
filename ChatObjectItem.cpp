#include "ChatObjectItem.h"
#include "ui_ChatObjectItem.h"

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
        ui->toolButtonClose->show();
        adjustLabelPostion();
    }

    QWidget::resizeEvent(e);
}

void ChatObjectItem::init()
{
    // 设置数据
    ui->labelHead->setPixmap(data->getHead());
    ui->labelNickname->setText(data->getName());
    ui->labelMessage->setText("messages....");

    adjustLabelText();

    adjustLabelPostion();

    initStyleSheet();
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
//    qDebug() << qss;
    this->setStyleSheet(qss);
    qDebug() << "load ChatObjectItem css";
}

zsj::Data::ptr ChatObjectItem::getData() const
{
    return data;
}
