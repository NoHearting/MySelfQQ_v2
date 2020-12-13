#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QDateTime>
#include <QSize>
#include <QPixmap>
#include <QBitmap>

namespace Zsj {


class Util
{
public:
    Util();
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

/// @brief 获取当前的时间
///
/// @param[in] 获取时间的格式，默认为yyyy-MM-dd
/// @return QString
inline QString GetCurrentDateTime(const QString & format = "yyyy-MM-dd"){
    return qPrintable(QDateTime::currentDateTime().toString(format));
}


}
#endif // UTIL_H
