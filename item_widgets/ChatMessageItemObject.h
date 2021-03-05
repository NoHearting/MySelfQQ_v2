/**
  * @file ChatMessageItemSelf.h
  * @brief 消息列表中的消息类型，显示消息和Emoji。显示在左边
  * @author zsj
  * @date 2021年3月3日09:57:18
  */
#ifndef CHATMESSAGEITEMOBJECT_H
#define CHATMESSAGEITEMOBJECT_H

#include <QWidget>

#include <QListWidgetItem>
#include <QSize>

#include "item_widgets/ChatMessageItem.h"
#include "main/ChatMessageData.h"

namespace Ui
{
class ChatMessageItemObject;
}

class ChatMessageItemObject : public QWidget, public zsj::ChatMessageItem
{
    Q_OBJECT

public:
    explicit ChatMessageItemObject(QWidget *parent = nullptr);
    ChatMessageItemObject(bool isLeft,zsj::ChatMessageData::ptr data, QListWidgetItem *item, QWidget *parent = nullptr);
    ~ChatMessageItemObject();


    void adjustWidgetsPosition()override;
    QSize calculateMessageWidgetSize()override;
    QSize getWidgetSize()override;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void initResourceAndForm();

private:
    Ui::ChatMessageItemObject *ui;

    QListWidgetItem *item;

    /// 聊天对象的数据  包括聊天信息、头像
    zsj::ChatMessageData::ptr chatMessageData;

    bool isLeft;


};

#endif // CHATMESSAGEITEMOBJECT_H
