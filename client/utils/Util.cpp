#include "Util.h"

#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>
#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QThread>
#include <QDir>
#include <QRegExp>


#include "main/ApplicationInfo.h"

namespace zsj
{

Util::Util()
{

}

QSize Util::ScaledImageSize(const QSize &originSize, int max)
{
    int realHeight = originSize.height();
    int realWidth = originSize.width();
    if(originSize.height() > originSize.width())
    {
        if(originSize.height() > max)
        {
            realHeight = max;
            realWidth = max * 1.0 / originSize.height() * originSize.width();
        }
    }
    else
    {
        if(originSize.width() > max)
        {
            realWidth = max;
            realHeight = max * 1.0 / originSize.width() * originSize.height();
        }
    }
    return QSize(realWidth, realHeight);
}

QString Util::PackageImageHtml(const QString &src, int width, int height)
{
    return QString("<img src='%1' width=%2 height=%3 />").arg(src).arg(width).arg(height);
}

QString Util::RemoveEnterReturn(const QString &origin)
{
    QString temp = origin;
//    return temp.replace("[\r\n]","");
    return temp.replace(QRegExp("[\r\n]"),"");
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
//    return qApp->applicationDirPath();
    return zsj::ApplicationInfo::Instance()->getAppAbsoluteDir();
}


int SystemUtil::getCurrentProcessId()
{
//    return qApp->applicationPid();
    return zsj::ApplicationInfo::Instance()->getAppPid();
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
        qDebug() << dirPath << " exist";
        return true;
    }
    QString parentDir = dirPath.mid(0, dirPath.lastIndexOf('/'));
    qDebug() << parentDir;
#ifdef Q_OS_WIN
    // window下创建文件夹因为是绝对路径有磁盘标识，如D:,C:,所以需要判断一下
    // 防止无限递归
    if((!parentDir.isEmpty() && !parentDir.isNull()) && parentDir[parentDir.size() - 1] != ':')
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
        if(!isOk)
        {
            qDebug() << "create dir failed";
            return false;
        }
    }
    return true;
}

QString HtmlUtil::RemoveOriginTagStyle(const QString &originStr, TagType types)
{

    QString result = originStr;
    for(auto iter = TagName.begin(); iter != TagName.end(); ++iter)
    {
        if(types & iter.value())
        {
            RemoveStyle(iter.key(), result);
        }
    }
    return result;
}

QString HtmlUtil::GetHtmlBodyContent(const QString &html)
{
    int begin = html.indexOf("<body");
    int bodyEnd = html.indexOf("</body>", begin);
    QString content = html.mid(begin, bodyEnd - begin + 7);
    return content;
}

void HtmlUtil::RemoveStyle(const QString &tag, QString &originStr)
{
    int index = 0;
    do
    {
        int begin = originStr.indexOf(QString("<%1 ").arg(tag), index);
        if(-1 == begin)
        {
            break;
        }
        int offset = QString(tag).size() + 1;
        int end = originStr.indexOf(">", begin + offset);
        QString temp = originStr.mid(begin, end - begin + 1);
        originStr.replace(temp, QString("<%1>").arg(tag));
        index = end;
    }
    while(index < originStr.size());
}





}
