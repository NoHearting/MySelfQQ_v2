#include "ChatMessageFileItemObject.h"
#include "ui_ChatMessageFileItemObject.h"

#include "main/ChatBubble.h"
#include "utils/Util.h"

ChatMessageFileItemObject::ChatMessageFileItemObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessageFileItemObject)
{
    ui->setupUi(this);
    initResourceAndForm();
}

ChatMessageFileItemObject::~ChatMessageFileItemObject()
{
    delete ui;
}

ChatMessageFileItemObject::ChatMessageFileItemObject(bool isLeft, zsj::ChatMessageData::ptr data,
        QListWidgetItem *item,
        QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessageFileItemObject),
    isLeft(isLeft),
    item(item),
    chatMessageData(data)
{
    ui->setupUi(this);
    initResourceAndForm();
}



void ChatMessageFileItemObject::initResourceAndForm()
{
    QPixmap ori = chatMessageData->getHead();
    QPixmap localHead = zsj::adjustToHead(ori, 32);
    ui->labelHead->setPixmap(localHead);
    int fontSize = zsj::ChatBubble::Instance()->getBubbleFontSize();

    QString fileName = chatMessageData->getFileName();
    int fileSize = chatMessageData->getFileSize();
    QString sizeStr;
    if(fileSize < 1024)
    {
        sizeStr = QString().asprintf("(%.2lfB)", fileSize * 1.0);
    }
    else
    {
        sizeStr = QString().asprintf("(%.2lfKB)", fileSize / 1024.0);
    }
    ui->labelName->setText(fileName);
    ui->labelSize->setText(sizeStr);
    ui->labelNote->setText("成功发送离线文件，文件助手暂存7天");
    ui->labelStatus->setPixmap(QPixmap(":/chat/res/chat/upload_success.png"));

    QString suffix = fileName.mid(fileName.indexOf(".") + 1);
    QPixmap logo(QString(":/chat/res/chat/%1.png").arg(suffix));
    if(logo.isNull())
    {
        logo.load(":/chat/res/chat/other.png");
    }
    ui->labelLogo->setPixmap(logo);

    this->setStyleSheet(QString(
                            "#widgetTools{border-top:1px solid rgb(136,136,136);}"
                            "#labelHead{border-radius:16px;border:none;}"
                            "#labelMessage{font-size:%1px;}"
                            "#widget{border-radius:5px;border:1px solid green;background:white;}"
                            "QPushButton{margin:0 5px 0;border:none;background:transparent;color:rgb(28,189,246);}"
                            "QPushButton:hover{text-decoration:underline}"
                            "#labelNote,#labelSize{color:rgb(136,136,136);}").arg(fontSize)
                       );
}

void ChatMessageFileItemObject::adjustLabelPosition()
{
    ui->labelName->adjustSize();
    ui->labelSize->adjustSize();
    ui->labelSize->setGeometry(ui->labelName->x() + ui->labelName->width() + 10,
                               ui->labelName->y(),
                               ui->labelSize->width(), ui->labelSize->height());
}

void ChatMessageFileItemObject::adjustWidgetsPosition()
{
    QSize size = ui->widget->size();
    if(isLeft)
    {
        ui->widget->setGeometry(QRect(50, 9, size.width(), size.height()));
    }
    else
    {
        ui->labelHead->setGeometry(width() - 41, 9, ui->labelHead->width(), ui->labelHead->height());
        ui->widget->setGeometry(QRect(width() - size.width() - 50, 9,
                                      size.width(), size.height()));
    }
    adjustLabelPosition();
}

QSize ChatMessageFileItemObject::calculateMessageWidgetSize()
{
    return QSize();
}

QSize ChatMessageFileItemObject::getWidgetSize()
{
    int padding = zsj::ChatBubble::Instance()->getBubblePadding();
    return QSize(ui->widget->width() + 18 + 2 * padding,
                 ui->widget->height() + 18 + 2 * padding);
}

void ChatMessageFileItemObject::resizeEvent(QResizeEvent *event)
{
    adjustWidgetsPosition();
    item->setSizeHint(getWidgetSize());
//    adjustImage();
    QWidget::resizeEvent(event);
}
