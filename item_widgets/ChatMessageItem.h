#ifndef CHATMESSAGEITEM_H
#define CHATMESSAGEITEM_H

#include <QSize>
#include <QFontMetrics>

namespace zsj {


class ChatMessageItem
{
public:
    /**
     * @brief HTML标签枚举，用于移除其样式匹配所用
     * @note 后续有需要继续添加
     */
    enum TagType{
        TAG_P = 0x0001,  // p标签
        TAG_IMG = 0x0002, // img标签
        TAG_SPAN = 0x0004, // span标签
        TAG_BODY = 0x008,   //body标签
        TAG_ALL = 0x1111    // 所有，用于运算
    };
public:
    ChatMessageItem();

    virtual QSize calculateMessageWidgetSize() = 0;
    virtual QSize getWidgetSize() = 0;
    virtual void adjustWidgetsPosition() = 0;

    /**
     * @brief 获取内容换行的最大长度
     * @param[in] content 内容
     * @param[in] currWidth 当前长度
     * @param[out] enterCount 换行的个数
     * @param[in] fm 用于检测文字宽度
     * @return
     */
    virtual int getContentMaxWidth(const QString & content,const int currWidth,
                                   int &enterCount,const QFontMetrics & fm);


    virtual ~ChatMessageItem();

private:
    /**
     * @brief 获取标签内部的内容长度
     * @param content 内容
     * @param fm
     * @return
     */
    int getTagContentWidth(const QString & content,const QFontMetrics & fm);

};

}

#endif // CHATMESSAGEITEM_H
