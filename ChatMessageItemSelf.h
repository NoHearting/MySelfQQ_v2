#ifndef CHATMESSAGEITEMSELF_H
#define CHATMESSAGEITEMSELF_H

#include <QWidget>

#include <QListWidgetItem>
#include <QSize>

#include "ChatMessageItem.h"
#include "ChatMessageData.h"

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

    ChatMessageItemSelf(zsj::ChatMessageData::ptr data, QListWidgetItem *item, QWidget *parent = nullptr);


    void adjustWidgetsPosition()override;
    QSize calculateMessageWidgetSize()override;
    QSize getWidgetSize()override;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void initResourceAndForm();
private:
    Ui::ChatMessageItemSelf *ui;


    QListWidgetItem *item;

    /// 聊天对象的数据  包括聊天信息、头像
    zsj::ChatMessageData::ptr chatMessageData = nullptr;
};

#endif // CHATMESSAGEITEMSELF_H
