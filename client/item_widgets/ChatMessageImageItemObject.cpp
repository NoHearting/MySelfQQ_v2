#include "ChatMessageImageItemObject.h"
#include "ui_ChatMessageImageItemObject.h"

#include "main/ChatBubble.h"
#include "utils/Util.h"
#include "main/CurrentWindow.h"

ChatMessageImageItemObject::ChatMessageImageItemObject(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatMessageImageItemObject)
{
    ui->setupUi(this);
    initResourceAndForm();
}

ChatMessageImageItemObject::ChatMessageImageItemObject(bool isLeft, zsj::ChatMessageData::ptr data,
        QListWidgetItem *item,
        QWidget *parent):
    QWidget(parent),
    ui(new Ui::ChatMessageImageItemObject),
    item(item),
    chatMessageData(data),
    isLeft(isLeft)
{
    ui->setupUi(this);
    initResourceAndForm();
}

ChatMessageImageItemObject::~ChatMessageImageItemObject()
{
    delete ui;
}

void ChatMessageImageItemObject::initResourceAndForm()
{
    QPixmap ori = chatMessageData->getHead();
    QPixmap localHead = zsj::adjustToHead(ori, 32);
    ui->labelHead->setPixmap(localHead);


    QString path = seprateImageSrc(chatMessageData->getImagePath());
    image = QPixmap(path);

    int fontSize = zsj::ChatBubble::Instance()->getBubbleFontSize();

    this->setStyleSheet(QString(
                            "#labelHead{border-radius:16px;border:none;}"
                            "#labelMessage{font-size:%1px;}"
                            "#widget{border-radius:5px;border:1px solid green;}").arg(fontSize)
                       );
}

void ChatMessageImageItemObject::adjustWidgetsPosition()
{
    QSize size = calculateMessageWidgetSize();
    qDebug() << "calculate size: " << size;
    int padding = zsj::ChatBubble::Instance()->getBubblePadding();
    if(isLeft)
    {
        ui->widget->setGeometry(QRect(50, 9, size.width(), size.height()));
    }
    else
    {
        ui->labelHead->setGeometry(this->width() - 41, padding, ui->labelHead->width(), ui->labelHead->height());
        ui->widget->setGeometry(QRect(this->width() - size.width() - 50, padding,
                                      size.width(), size.height()));
    }
}

QSize ChatMessageImageItemObject::calculateMessageWidgetSize()
{
    QRect windowGeometry = zsj::CurrentWindow::Instance()->getWindowGeometry();
    QSize size = currentEnableImageSize(windowGeometry.size()) * 0.8;
    return size;
}

QSize ChatMessageImageItemObject::getWidgetSize()
{
    int padding = zsj::ChatBubble::Instance()->getBubblePadding();
    return QSize(ui->widget->width()  + 2 * padding,
                 ui->widget->height()  + 2 * padding);
}

void ChatMessageImageItemObject::adjustImage()
{
    QSize size = calculateMessageWidgetSize();
    QPixmap tempPix = zsj::scaledPixmap(image, size.width(), size.height());
    ui->labelMessage->setPixmap(tempPix);
}

void ChatMessageImageItemObject::resizeEvent(QResizeEvent *event)
{
    adjustWidgetsPosition();
    item->setSizeHint(getWidgetSize());
    adjustImage();
    QWidget::resizeEvent(event);
}



QSize ChatMessageImageItemObject::currentEnableImageSize(QSize windowSize)
{
    QPixmap pix(chatMessageData->getImagePath());
    if(!pix.isNull())
    {
        int width = windowSize.width() / 2;
        int height = windowSize.height() / 2;
        if(pix.width() <= width && pix.height() <= height)
        {
            return QSize(width, height);
        }
        else if(pix.width() > width && pix.height() < height)
        {
            height = (width * 1.0 / pix.width()) * pix.height();
        }
        else if(pix.width() <= width && pix.height() > height)
        {
            width = (height * 1.0 / pix.height()) * pix.width();
        }
        else if(pix.width() > width && pix.height() > height)
        {
            float heightDivisor = height * 1.0 / pix.height();
            float widthDivisor = width * 1.0 / pix.width();
            float minDivisor = heightDivisor > widthDivisor ?
                               widthDivisor : heightDivisor;
            width = pix.width() * minDivisor;
            height = pix.height() * minDivisor;
        }
        return QSize(width, height);
    }
    else
    {
        qCritical() << chatMessageData->getImagePath() << " is null!";
        return QSize();
    }
}

QString ChatMessageImageItemObject::seprateImageSrc(const QString &imgTag)
{
    if(imgTag.contains("<img"))
    {
        int begin = imgTag.indexOf("src=\"");
        int end = imgTag.indexOf("\"", begin + 6);
        QString path = imgTag.mid(begin + 5, end - begin - 5);
        chatMessageData->setImagePath(path);
        return path;
    }
    else
    {
        return imgTag;
    }
}
