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
#include <QMap>

#include "utils/Global.h"

# define DEBUG 1

namespace zsj
{


class Util
{
public:
    Util();
    /**
     * @brief 自适应长宽
     * @param originSize 原来的大小
     * @param max 最大的大小
     * @return 适应后的Size
     * @note 主要用于截图后粘贴到输入框中
     */
    static QSize ScaledImageSize(const QSize & originSize,int max = 150 );

    /**
     * @brief 将文件路径打包为html中的<src>样式
     * @param src 文件路径
     * @param width 宽
     * @param height 高
     * @return <img src="#src" width=#width height=#height />
     */
    static QString PackageImageHtml(const QString & src,int width,int height);


    /**
     * @brief 去掉字符串中的回车换行
     * @param origin
     * @return
     */
    static QString RemoveEnterReturn(const QString & origin);
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


    /**
     * @brief 获取程序运行路径
     * @return
     */
    static QString getProcessPath();
};


class FileUtil{
public:
    /**
     * @brief 判断目录是否存在，不存在就创建
     * @param dirPath 需要判断的目录
     * @return 目录存在和创建成功返回true，否则返回false
     */
    static bool judgeAndMakeDir(const QString & dirPath);
};





/**
 * @brief HTML标签枚举，用于移除其样式匹配所用
 * @note 后续有需要继续添加
 */
enum TagType{
    TAG_P           = 0x000001,         // p标签
    TAG_IMG         = 0x000000,         // img标签
    TAG_SPAN        = 0x000004,         // span标签
    TAG_BODY        = 0x000008,         // body标签
    TAG_H1          = 0x000010,         // h4
    TAG_H2          = 0x000020,         // h4
    TAG_H3          = 0x000040,         // h3
    TAG_H4          = 0x000080,         // h4
    TAG_H5          = 0x000100,         // h5
    TAG_ALL_H       = 0x0001F0,         // 所有h标签
    TAG_UL          = 0x000200,         // ul
    TAG_OL          = 0x000400,         // ol
    TAG_LI          = 0x000800,         // li
    TAG_ALL_TABLE   = 0x000E00,         // 所有表格标签
    TAG_ALL         = 0xFFFFFF          // 所有，用于运算
};

static const QMap<QString,TagType> TagName = {
    {"p",TAG_P},
    {"span",TAG_SPAN},
    {"body",TAG_BODY},
    {"h1",TAG_H1},{"h2",TAG_H2},{"h3",TAG_H3},{"h4",TAG_H4},{"h5",TAG_H5},
    {"ul",TAG_UL},{"ol",TAG_OL},{"li",TAG_LI}
};


static const QMap<TagType,QString> NameTag = {
    {TAG_P,"p"},
    {TAG_SPAN,"span"},
    {TAG_BODY,"body"},
    {TAG_H1,"h1"},{TAG_H2,"h2"},{TAG_H3,"h3"},{TAG_H4,"h4"},{TAG_H5,"h5"},
    {TAG_UL,"ul"},{TAG_OL,"ol"},{TAG_LI,"li"}
};

class HtmlUtil{
public:
    /**
     * @brief 移除HTML标签中Qt自带的style样式
     * @param originStr 原始字符串
     * @param types 需要移除样式的标签
     * @return
     * @note 移除样式之后方便计算其宽度
     */
    static QString RemoveOriginTagStyle(const QString & originStr,TagType types);

    /**
     * @brief 获取html文档中的body内容
     * @param html html文档
     * @return
     */
    static QString GetHtmlBodyContent(const QString & html);

private:
    /**
     * @brief 移除标签的内联样式
     * @param types 需要移除的标签类型
     * @param originStr
     */
    static void RemoveStyle(const QString & tag,QString & originStr);
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
