#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QDateTime>
#include <QSize>
#include <QPixmap>
#include <QBitmap>
#include <QDesktopServices>
#include <QUrl>
#include <QColor>
#include <QWidget>
#include <utility>
#include <QDebug>

#include "utils/Global.h"

# define DEBUG 1

namespace zsj
{


class Util
{
public:
    Util();
};

struct HeadSize
{

    /// 登录界面主头像
    static const quint8 loginMainDiameter = 64;

    /// 登了界面下拉框候选项头像
    static const quint8 loginItemDiameter = 40;

    /// 主页面头像
    static const quint8 mainDiamter = 54;

    /// 联系人列表中好友头像
    static const quint8 linkmanItemDiameter = 40;

    /// 联系人列表中群组头像
    static const quint8 linkmanGroupDiameter = 30;

    /// 消息列表中头像
    static const quint8 messageItemDiameter = 40;
};


class WidgetUtil
{
public:
    static void setWidgetBoxShadow(QWidget *widget, int offsetX = 0, int offsetY = 0,
                                   const QColor &color = Qt::black, int radius = 5);

    template<typename originParent,typename originItem,typename target>
    static target * widgetCast(originParent * parentWidget,originItem * item){

        if(!parentWidget || !item){
            qCritical() << "paramter is nullptr";
            return nullptr;
        }
        QWidget * widget = parentWidget->itemWidget(item);
        if(widget){
            target * obj = dynamic_cast<target*>(widget);
            if(obj){
                return obj;
            }
        }
        return nullptr;

    }
};

class SystemUtil
{
public:
    /// @brief 获取当前进程id
    static int getCurrentProcessId();

    /// @brief 获取当前桌面大小
    /// @return QSize
    static QSize getDesktopSize();


    /// @brief 获取当前可用左面的位置大小
    /// @return QRect
    static QRect getAvailableGeometry();

    /// @brief 获取当前可用桌面大小，不包含工具栏
    static QSize getAvailableDesktopSize();


    /// @brief 获取当前线程id
    /// @return QString
    static QString getCurrentThreadId();
};




/// @brief 将QPixmap转换为圆形
///
/// @param[in] src 将要转换的pixmap
/// @param[in] radius 转换后圆形的半径
/// @param QPixmap
QPixmap pixmapToRound(QPixmap &src, int radius);


/// @brief 等比缩放图片
///
/// @param[in] src 将要处理的图片
/// @param[in] width 目标图片的宽
/// @param[in] height 目标图片的高
/// @return QPixmap
QPixmap scaledPixmap(QPixmap &src, int width, int height);

/// @brief 直接缩放为适应头像大小
///     主要是先缩放，在变为圆形
///     scaledPixmap + pixmapToRound
/// @param[in] src 将要处理的图片
/// @param[in] diameter 目标图片直径
QPixmap adjustToHead(QPixmap &src, int diameter);

/// @brief 获取当前的时间
///
/// @param[in] 获取时间的格式，默认为yyyy-MM-dd
/// @return QString
inline QString GetCurrentDateTime(const QString &format = "yyyy-MM-dd")
{
    return qPrintable(QDateTime::currentDateTime().toString(format));
}


/// @brief 打开url
///
/// @param QString url
void openUrl(const QString &url = "http://www.xl-zsj.top");

/// @brief 检查QPixmap是否为空，如果为空则设置一个默认QPixmap
///
/// @param[in/out] 需要检查的QPixmap
/// @param[in] 默认的QPixmap
bool checkAndSetPixmap(QPixmap &src, const QString defaultPixmapPath);
bool checkAndSetPixmap(QPixmap &src, const QPixmap &defaultPixmap);




}
#endif // UTIL_H
