#include "Util.h"

#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>

namespace Zsj{

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



}
