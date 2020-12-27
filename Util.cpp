#include "Util.h"

#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include <QGraphicsDropShadowEffect>

namespace zsj{

Util::Util()
{

}


int getCurrentProcessId()
{
    return qApp->applicationPid();
}

QSize getDesktopSize()
{
    QWidget * screen = qApp->desktop()->screen();
    return QSize(screen->width(),screen->height());
}


QPixmap pixmapToRound(QPixmap &src, int radius)
{
    if (src.isNull()) {
            return QPixmap();
    }

    QSize size(2*radius, 2*radius);
    QBitmap mask(size);
    QPainter painter(&mask);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 99, 99);

    QPixmap image = src.scaled(size);
    image.setMask(mask);
    return image;
}

QPixmap scaledPixmap(QPixmap &src, int width, int height)
{
    return src.scaled(width,height,Qt::KeepAspectRatio,Qt::SmoothTransformation);
}

void openUrl(const QString &url)
{
    QDesktopServices::openUrl(QUrl(url));
}

QPixmap adjustToHead(QPixmap &src, int diameter)
{
    bool ret = zsj::checkAndSetPixmap(src,":/global/res/global/error.png");
    if(!ret){
        qCritical() << "pixmap is null!";
    }
    QPixmap scaled = scaledPixmap(src,diameter,diameter);
    return pixmapToRound(scaled,diameter / 2);
}

bool checkAndSetPixmap(QPixmap &src, const QString defaultPixmapPath)
{
    if(src.isNull()){
        src.load(defaultPixmapPath);
        return false;
    }
    else{
        return true;
    }
}

bool checkAndSetPixmap(QPixmap &src, const QPixmap &defaultPixmap)
{
    if(src.isNull()){
        src = defaultPixmap;
        return false;
    }
    else{
        return true;
    }
}

void WidgetUtil::setWidgetBoxShadow(QWidget *widget, int offsetX, int offsetY, const QColor &color, int radius)
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setOffset(offsetX,offsetY);  //阴影偏移量
    shadow->setColor(color);  //阴影颜色
    shadow->setBlurRadius(radius);     //阴影的模糊半径
    widget->setGraphicsEffect(shadow);
}



}
