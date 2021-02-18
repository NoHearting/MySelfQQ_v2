#include "Util.h"

#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QThread>
#include <QDir>

namespace zsj
{

Util::Util()
{

}

QSize Util::ScaledImageSize(const QSize &originSize, int max)
{
    int realHeight = originSize.height();
    int realWidth = originSize.width();
    if(originSize.height() > originSize.width()){
        if(originSize.height() > max){
            realHeight = max;
            realWidth = max * 1.0 / originSize.height() * originSize.width();
        }
    }
    else{
        if(originSize.width() > max){
            realWidth = max;
            realHeight = max * 1.0 / originSize.width() * originSize.height();
        }
    }
    return QSize(realWidth,realHeight);
}




QPixmap pixmapToRound(QPixmap &src, int radius)
{
    if (src.isNull())
    {
        return QPixmap();
    }

    QSize size(2 * radius, 2 * radius);
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
    return src.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

void openUrl(const QString &url)
{
    QDesktopServices::openUrl(QUrl(url));
}

QPixmap adjustToHead(QPixmap &src, int diameter)
{
    bool ret = zsj::checkAndSetPixmap(src, ":/global/res/global/error.png");
    if(!ret)
    {
        qCritical() << "pixmap is null!";
    }
    QPixmap scaled = scaledPixmap(src, diameter, diameter);
    return pixmapToRound(scaled, diameter / 2);
}

bool checkAndSetPixmap(QPixmap &src, const QString defaultPixmapPath)
{
    if(src.isNull())
    {
        src.load(defaultPixmapPath);
        return false;
    }
    else
    {
        return true;
    }
}

bool checkAndSetPixmap(QPixmap &src, const QPixmap &defaultPixmap)
{
    if(src.isNull())
    {
        src = defaultPixmap;
        return false;
    }
    else
    {
        return true;
    }
}

void WidgetUtil::setWidgetBoxShadow(QWidget *widget, int offsetX, int offsetY, const QColor &color, int radius)
{
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(widget);
    shadow->setOffset(offsetX, offsetY); //阴影偏移量
    shadow->setColor(color);  //阴影颜色
    shadow->setBlurRadius(radius);     //阴影的模糊半径
    widget->setGraphicsEffect(shadow);
}

QString SystemUtil::getCurrentThreadId()
{
    QString threadText = QString("%1").arg(quintptr(QThread::currentThreadId()));
    return threadText;
}

QString SystemUtil::getProcessPath()
{
    return qApp->applicationDirPath();
}


int SystemUtil::getCurrentProcessId()
{
    return qApp->applicationPid();
}

QSize SystemUtil::getDesktopSize()
{
    QWidget *screen = qApp->desktop()->screen();
    return QSize(screen->width(), screen->height());
}

QRect SystemUtil::getAvailableGeometry()
{
    return qApp->desktop()->availableGeometry();
}

QSize SystemUtil::getAvailableDesktopSize()
{
    return qApp->desktop()->availableGeometry().size();
}

bool FileUtil::judgeAndMakeDir(const QString &dirPath)
{
    QDir dir(dirPath);
    if(dir.exists(dirPath))
    {
        return true;
    }
    QString parentDir = dirPath.mid(0, dirPath.lastIndexOf('/'));
    qDebug() << parentDir;
#ifdef Q_OS_WIN
    // window下创建文件夹因为是绝对路径有磁盘标识，如D:,C:,所以需要判断一下
    // 防止无限递归
    if(parentDir[parentDir.size() - 1] != ':')
    {
        judgeAndMakeDir(parentDir);
    }
#elif defined(Q_OS_LINUX)
    judgeAndMakeDir(parentDir);
#endif
    QString dirname = dirPath.mid(dirPath.lastIndexOf('/') + 1);
    QDir parentPath(parentDir);
    if(!dirname.isEmpty())
    {
        bool isOk = parentPath.mkpath(dirname);
        if(isOk)
        {
            return true;
        }
        else
        {
            qDebug() << "create dir failed";
            return false;
        }
    }
    return false;
}



}
