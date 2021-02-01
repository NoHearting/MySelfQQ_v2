#ifndef CHATMESSAGEITEM_H
#define CHATMESSAGEITEM_H

#include <QSize>

namespace zsj {


class ChatMessageItem
{
public:
    ChatMessageItem();

    virtual QSize calculateMessageWidgetSize() = 0;
    virtual QSize getWidgetSize() = 0;
    virtual void adjustWidgetsPosition() = 0;

    ~ChatMessageItem();

};

}

#endif // CHATMESSAGEITEM_H
