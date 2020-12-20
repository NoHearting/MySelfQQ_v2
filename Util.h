#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QDateTime>
#include <QSize>
#include <QPixmap>
#include <QBitmap>
#include <QDesktopServices>
#include <QUrl>

# define DEBUG 1

namespace Zsj {


class Util
{
public:
    Util();
};

struct HeadSize{
    /// 主页面头像
    static const quint8 mainWidth = 54;
    static const quint8 mainHeight = 54;

    /// 联系人列表中好友头像
    static const quint8 linkmanItemWidth = 40;
    static const quint8 linkmanItemHeight = 40;

    /// 联系人列表中群组头像
    static const quint8 linkmanGroupWidth = 30;
    static const quint8 linkmanGroupHeight = 30;

    /// 消息列表中头像
    static const quint8 messageItemWidth = 40;
    static const quint8 messageItemHeight = 40;
};

/// @brief 获取当前进程id
int getCurrentProcessId();

/// @brief 获取当前桌面大小
/// @return QSize
QSize getDesktopSize();

/// @brief 将QPixmap转换为圆形
///
/// @param[in] src 将要转换的pixmap
/// @param[in] radius 转换后圆形的半径
/// @param QPixmap
QPixmap pixmapToRound(QPixmap & src,int radius);


/// @brief 等比缩放图片
///
/// @param[in] src 将要处理的图片
/// @param[in] width 目标图片的宽
/// @param[in] height 目标图片的高
/// @return QPixmap
QPixmap scaledPixmap(QPixmap & src,int width,int height);

/// @brief 直接缩放为适应头像大小
///     主要是先缩放，在变为圆形
///     scaledPixmap + pixmapToRound
/// @param[in] src 将要处理的图片
/// @param[in] diameter 目标图片直径
QPixmap adjustToHead(QPixmap & src,int diameter);

/// @brief 获取当前的时间
///
/// @param[in] 获取时间的格式，默认为yyyy-MM-dd
/// @return QString
inline QString GetCurrentDateTime(const QString & format = "yyyy-MM-dd"){
    return qPrintable(QDateTime::currentDateTime().toString(format));
}


/// @brief 打开url
///
/// @param QString url
void openUrl(const QString & url = "http://www.xl-zsj.top");


}
#endif // UTIL_H
