#include "ChatMessageRecord.h"

#include<QDebug>

#include "utils/Util.h"
namespace zsj
{


ChatMessageRecord::ChatMessageRecord() :
    dateTime(QDateTime::currentDateTime()),
    sender(0), receiver(0), messageBody(nullptr)
{

}

ChatMessageRecord::ChatMessageRecord(QDateTime dateTime,
                                     quint64 sender,
                                     quint64 receiver,
                                     MessageBodyPtr messageBody):
    dateTime(dateTime), sender(sender), receiver(receiver),
    messageBody(messageBody)
{

}

ChatMessageRecord::ChatMessageRecord(QDateTime dateTime,
                                     quint64 sender,
                                     quint64 receiver):
    dateTime(dateTime), sender(sender), receiver(receiver),
    messageBody(nullptr)
{

}

ChatMessageRecord ChatMessageRecord::DeserializationFromJson(
    const QString &jsonString)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toLatin1());
    if(!doc.isEmpty() && !doc.isNull())
    {
        QJsonObject obj = doc.object();
        QDateTime dateTime = QDateTime::fromString(obj.value("dateTime").toString(),
                             "yyyy-MM-dd hh:mm:ss");
        quint64 sender = obj.value("sender").toInt();
        quint64 receiver = obj.value("receiver").toInt();
        QJsonObject msgObj = obj.value("msgBody").toObject();
        QString msgBodyStr(QJsonDocument(msgObj).toJson().data());
        MessageBodyPtr messageBody =
            MessageBody::DeserializationFromJson(msgBodyStr);
        return ChatMessageRecord(dateTime, sender, receiver, messageBody);
    }
    else
    {
        qCritical() << "deserialize from json to text message body failed!";
    }
    return ChatMessageRecord();
}



QString ChatMessageRecord::serializeToJson()
{
    QJsonObject obj;
    obj.insert("dateTime", QJsonValue(dateTime.toString("yyyy-MM-dd hh:mm:ss")));
    obj.insert("sender", QJsonValue(static_cast<qint64>(sender)));
    obj.insert("receiver", QJsonValue(static_cast<qint64>(receiver)));
    QJsonObject msgObj;
    if(!messageBody.isNull())
    {
        msgObj = messageBody->serializeToJsonObject();
    }
    obj.insert("msgBody", QJsonValue(msgObj));
    return zsj::Util::RemoveEnterReturn(QString(QJsonDocument(obj).toJson()));
}

MessageBodyPtr ChatMessageRecord::getMessageBody() const
{
    return messageBody;
}

void ChatMessageRecord::setMessageBody(const MessageBodyPtr &value)
{
    messageBody = value;
}

QDateTime ChatMessageRecord::getDateTime() const
{
    return dateTime;
}

void ChatMessageRecord::setDateTime(const QDateTime &value)
{
    dateTime = value;
}

quint64 ChatMessageRecord::getSender() const
{
    return sender;
}

void ChatMessageRecord::setSender(const quint64 &value)
{
    sender = value;
}

quint64 ChatMessageRecord::getReceiver() const
{
    return receiver;
}

void ChatMessageRecord::setReceiver(const quint64 &value)
{
    receiver = value;
}



MessageBodyPtr MessageBody::DeserializationFromJson(const QString &jsonString)
{
    if(jsonString.contains("TEXT"))
    {
        return TextMessageBody::DeserializationFromJson(jsonString);
    }
    else if(jsonString.contains("IMAGE"))
    {
        return ImageMessageBody::DeserializationFromJson(jsonString);
    }
    else if(jsonString.contains("FILE"))
    {
        return ImageMessageBody::DeserializationFromJson(jsonString);
    }
    else if(jsonString.contains("AUDIO"))
    {
        qDebug() << "deserialize from json to audio message body";
        return MessageBodyPtr(nullptr);
    }
    else if(jsonString.contains("VEDIO"))
    {
        qDebug() << "deserialize from json to vedio message body";
        return MessageBodyPtr(nullptr);
    }
    else
    {
        qCritical() << "deserialize failed!!!";
        return MessageBodyPtr(nullptr);
    }
}

MessageBodyPtr TextMessageBody::DeserializationFromJson(const QString &jsonString)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toLatin1());
    if(!doc.isEmpty() && !doc.isNull())
    {
        QJsonObject obj = doc.object();
        QString content = obj.value("content").toString();
        return MessageBodyPtr(new TextMessageBody(content));
    }
    else
    {
        qCritical() << "deserialize from json to text message body failed!";
    }
    return nullptr;
}

TextMessageBody::TextMessageBody(const QString &content,
                                 global::MessageType type) :
    MessageBody(), content(content), type(type)
{

}

QString TextMessageBody::serializeToJson()
{
    QJsonObject obj = serializeToJsonObject();
    return QString(QJsonDocument(obj).toJson());
}

QJsonObject TextMessageBody::serializeToJsonObject()
{
    QJsonObject obj;
    obj.insert("content", QJsonValue(content));
    obj.insert("type", "TEXT");
    return obj;
}

QString TextMessageBody::getContent() const
{
    return content;
}

void TextMessageBody::setContent(const QString &value)
{
    content = value;
}

global::MessageType TextMessageBody::getType() const
{
    return type;
}

void TextMessageBody::setType(const global::MessageType &value)
{
    type = value;
}

MessageBodyPtr ImageMessageBody::DeserializationFromJson(const QString &jsonString)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toLatin1());
    if(!doc.isEmpty() && !doc.isNull())
    {
        QJsonObject obj = doc.object();
        QString content = obj.value("content").toString();
        return MessageBodyPtr(new ImageMessageBody(content));
    }
    else
    {
        qCritical() << "deserialize from json to image message body failed!";
    }
    return MessageBodyPtr(nullptr);
}

ImageMessageBody::ImageMessageBody(const QString &content,
                                   global::MessageType type) :
    MessageBody(), content(content),
    type(type)
{

}

QString ImageMessageBody::serializeToJson()
{
    QJsonObject obj = serializeToJsonObject();
    return QString(QJsonDocument(obj).toJson());
}

QJsonObject ImageMessageBody::serializeToJsonObject()
{
    QJsonObject obj;
    obj.insert("content", QJsonValue(content));
    obj.insert("type", "IMAGE");
    return obj;
}

QString ImageMessageBody::getContent() const
{
    return content;
}

void ImageMessageBody::setContent(const QString &value)
{
    content = value;
}

global::MessageType ImageMessageBody::getType() const
{
    return type;
}

void ImageMessageBody::setType(const global::MessageType &value)
{
    type = value;
}

MessageBodyPtr FileMessageBody::DeserializationFromJson(const QString &jsonString)
{
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toLatin1());
    if(!doc.isEmpty() && !doc.isNull())
    {
        QJsonObject obj = doc.object();
        QString fileName = obj.value("fileName").toString();
        QString filePath = obj.value("filePath").toString();
        int fileSize = obj.value("fileSize").toInt();
        return MessageBodyPtr(new FileMessageBody(fileName, filePath, fileSize));
    }
    else
    {
        qCritical() << "deserialize from json to file message body failed!";
    }
    return MessageBodyPtr(nullptr);
}

FileMessageBody::FileMessageBody(const QString &fileName,
                                 const QString &filePath,
                                 int fileSize,
                                 global::MessageType type) :
    MessageBody(), fileName(fileName), filePath(filePath),
    fileSize(fileSize), type(type)
{

}

QString FileMessageBody::serializeToJson()
{
    QJsonObject obj = serializeToJsonObject();
    return QString(QJsonDocument(obj).toJson());
}

QJsonObject FileMessageBody::serializeToJsonObject()
{
    QJsonObject obj;
    obj.insert("fileName", QJsonValue(fileName));
    obj.insert("filePatj", QJsonValue(filePath));
    obj.insert("fileSize", QJsonValue(fileSize));
    obj.insert("type", "FILE");
    return obj;
}

QString FileMessageBody::getContent() const
{
    return QString();
}

void FileMessageBody::setContent(const QString &)
{

}

global::MessageType FileMessageBody::getType() const
{
    return type;
}

void FileMessageBody::setType(const global::MessageType &value)
{
    type = value;
}

QString FileMessageBody::getFileName() const
{
    return fileName;
}

QString FileMessageBody::getFilePath() const
{
    return filePath;
}

int FileMessageBody::getFileSize() const
{
    return fileSize;
}



}


