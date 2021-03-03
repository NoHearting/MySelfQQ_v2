#ifndef CHATMESSAGEITEMSELF_H
#define CHATMESSAGEITEMSELF_H

#include <QWidget>
/**
  * @file ChatMessageItemSelf.h
  * @brief 消息列表中的消息类型，显示消息和Emoji。显示在右边
  * @author zsj
  * @date 2021年3月3日09:57:18
  */
#include <QListWidgetItem>
#include <QSize>

#include "item_widgets/ChatMessageItem.h"
#include "main/ChatMessageData.h"

namespace Ui
{
class ChatMessageItemSelf;
}

class ChatMessageItemSelf : public QWidget, public zsj::ChatMessageItem
{
    Q_OBJECT

public:
    explicit ChatMessageItemSelf(QWidget *parent = nullptr);
    ~ChatMessageItemSelf();

    ChatMessageItemSelf(zsj::ChatMessageData::ptr data, QListWidgetItem *item,
                        QWidget *parent = nullptr);


    void adjustWidgetsPosition()override;
    QSize calculateMessageWidgetSize()override;
    QSize getWidgetSize()override;

protected:
    /**
     * @brief 每次触发这个信号时，需要重新设置各个widget的大小和位置
     * @param event
     */
    void resizeEvent(QResizeEvent *event);

private:
    void initResourceAndForm();
private:
    Ui::ChatMessageItemSelf *ui;


    QListWidgetItem *item;

    /// 聊天对象的数据  包括聊天信息、头像
    zsj::ChatMessageData::ptr chatMessageData;

};

#endif // CHATMESSAGEITEMSELF_H
