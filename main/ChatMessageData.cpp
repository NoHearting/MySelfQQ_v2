#include "ChatMessageData.h"

#include <memory>

#include <QDebug>

namespace zsj
{



ChatMessageData::ChatMessageData()
{

}

ChatMessageData::ChatMessageData(QPixmap &head, const ChatMessageRecord &chatMessageRecord) :
    head(head), chatMessageRecord(chatMessageRecord)
{

}

//ChatMessageData::ChatMessageData(const QString &imagePath, QPixmap &head):
//    head(head), imagePath(imagePath)
//{

//}

//ChatMessageData::ChatMessageData(QPixmap &head, const QString &message, bool hasEmoji) :
//    head(head),
//    message(message),
//    hasEmoji(hasEmoji)
//{

//}

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
//    return message;
    return chatMessageRecord.getMessageBody()->getContent();
}

void ChatMessageData::setMessage(const QString &value)
{
    chatMessageRecord.getMessageBody()->setContent(value);
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
    return chatMessageRecord.getMessageBody()->getContent();
}

void ChatMessageData::setImagePath(const QString &value)
{
    chatMessageRecord.getMessageBody()->setContent(value);
}

zsj::ChatMessageRecord ChatMessageData::getChatMessageRecord() const
{
    return chatMessageRecord;
}

void ChatMessageData::setChatMessageRecord(const zsj::ChatMessageRecord &value)
{
    chatMessageRecord = value;
}

QString ChatMessageData::getFilePath() const
{
    if(chatMessageRecord.getMessageBody()->getType() ==
            zsj::global::MessageType::FILE)
    {
        FileMessageBody *fileBody = dynamic_cast<FileMessageBody *>(chatMessageRecord.getMessageBody().get());
        if(fileBody)
        {
            return fileBody->getFilePath();
        }
        else
        {
            qCritical() << "MessageBody dynamic cast to FileMessageBody failed!";
        }
    }
    else
    {
        return "";
    }
}

QString ChatMessageData::getFileName() const
{
    if(chatMessageRecord.getMessageBody()->getType() ==
            zsj::global::MessageType::FILE)
    {
//        QSharedPointer<FileMessageBody> fileBody =
//                std::dynamic_pointer_cast<FileMessageBody>(chatMessageRecord.getMessageBody());
        FileMessageBody *fileBody = dynamic_cast<FileMessageBody *>(chatMessageRecord.getMessageBody().get());
        if(fileBody)
        {
            return fileBody->getFileName();
        }
        else
        {
            qCritical() << "MessageBody dynamic cast to FileMessageBody failed!";
        }

    }
    else
    {
        return "";
    }
}

int ChatMessageData::getFileSize() const
{
    if(chatMessageRecord.getMessageBody()->getType() ==
            zsj::global::MessageType::FILE)
    {
        FileMessageBody *fileBody = dynamic_cast<FileMessageBody *>(chatMessageRecord.getMessageBody().get());
        if(fileBody)
        {
            return fileBody->getFileSize();
        }
        else
        {
            qCritical() << "MessageBody dynamic cast to FileMessageBody failed!";
        }
    }
    else
    {
        return -1;
    }
}




}
