#ifndef CHATMESSAGEFILEITEMOBJECT_H
#define CHATMESSAGEFILEITEMOBJECT_H

#include <QWidget>
#include <QListWidget>


#include "item_widgets/ChatMessageItem.h"
#include "main/ChatMessageData.h"

namespace Ui
{
class ChatMessageFileItemObject;
}

class ChatMessageFileItemObject : public QWidget, public zsj::ChatMessageItem
{
    Q_OBJECT

public:
    explicit ChatMessageFileItemObject(QWidget *parent = nullptr);
    ~ChatMessageFileItemObject();
    ChatMessageFileItemObject(bool isLeft,zsj::ChatMessageData::ptr data, QListWidgetItem *item,
                              QWidget *parent = nullptr);

    void adjustWidgetsPosition() override;
    QSize calculateMessageWidgetSize() override;
    QSize getWidgetSize()override;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    void initResourceAndForm();

    /**
     * @brief 每次都要自适应label的位置
     */
    void adjustLabelPosition();
private:
    Ui::ChatMessageFileItemObject *ui;

    bool isLeft;

    QListWidgetItem *item;

    /// 聊天对象的数据
    zsj::ChatMessageData::ptr chatMessageData;
};

#endif // CHATMESSAGEFILEITEMOBJECT_H
