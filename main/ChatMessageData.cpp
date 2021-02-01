#include "ChatMessageData.h"

namespace zsj {



ChatMessageData::ChatMessageData()
{

}

ChatMessageData::ChatMessageData(QPixmap &head, const QString &message) :
    head(head),
    message(message)
{

}

QPixmap ChatMessageData::getHead() const
{
    return head;
}

void ChatMessageData::setHead(const QPixmap &value)
{
    head = value;
}

QString ChatMessageData::getMessage() const
{
    return message;
}

void ChatMessageData::setMessage(const QString &value)
{
    message = value;
}
}
