#include "ChatMessageData.h"

namespace zsj
{



ChatMessageData::ChatMessageData()
{

}

ChatMessageData::ChatMessageData(const QString &imagePath, QPixmap &head):
    head(head), imagePath(imagePath)
{

}

ChatMessageData::ChatMessageData(QPixmap &head, const QString &message, bool hasEmoji) :
    head(head),
    message(message),
    hasEmoji(hasEmoji)
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

bool ChatMessageData::getHasEmoji() const
{
    return hasEmoji;
}

void ChatMessageData::setHasEmoji(bool value)
{
    hasEmoji = value;
}

QString ChatMessageData::getImagePath() const
{
    return imagePath;
}

void ChatMessageData::setImagePath(const QString &value)
{
    imagePath = value;
}

}
