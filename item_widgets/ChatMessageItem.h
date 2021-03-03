/**
  * @file ChatMessageItem.h
  * @brief 显示聊天单条记录的item的基类。主要是处理自适应内容
  * @author zsj
  * @date 2021年3月3日09:48:30
  */
#ifndef CHATMESSAGEITEM_H
#define CHATMESSAGEITEM_H

#include <QSize>
#include <QFontMetrics>

namespace zsj {


class ChatMessageItem
{
public:
    ChatMessageItem();

    /**
     * @brief 计算内容容器（放置消息内容）的Size。
     * @return
     */
    virtual QSize calculateMessageWidgetSize() = 0;

    /**
     * @brief 获取布局容器（包含内容容器）的Size
     * @return
     * @note 需要先计算出内容容器的Size
     */
    virtual QSize getWidgetSize() = 0;

    /**
     * @brief 设置布局容器的位置
     */
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
