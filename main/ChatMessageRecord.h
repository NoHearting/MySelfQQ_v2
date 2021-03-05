/**
  * @file ChatMessageRecord.h
  * @brief 聊天记录数据
  * @author zsj
  * @date 时间
  */
#ifndef CHATMESSAGERECORD_H
#define CHATMESSAGERECORD_H

#include <QDateTime>
#include <QString>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QSharedPointer>
#include <QJsonArray>

#include "utils/Global.h"

namespace zsj
{


class MessageBody;

typedef QSharedPointer<MessageBody> MessageBodyPtr;

class ChatMessageRecord
{
public:
    /**
     * @brief 从Json字符串反序列化
     * @param jsonString
     * @return
     */
    static ChatMessageRecord DeserializationFromJson(const QString &jsonString);
public:
    ChatMessageRecord();
    ChatMessageRecord(QDateTime dateTime, const QString &sender,
                      const QString &receiver, MessageBodyPtr messageBody);
    ChatMessageRecord(QDateTime dateTime, const QString &sender,
                      const QString &receiver);

    /**
     * @brief 序列化为Json字符串
     * @return
     */
    QString serializeToJson();

    MessageBodyPtr getMessageBody() const;
    void setMessageBody(const MessageBodyPtr &value);

    QDateTime getDateTime() const;
    void setDateTime(const QDateTime &value);

    QString getSender() const;
    void setSender(const QString &value);

    QString getReceiver() const;
    void setReceiver(const QString &value);

private:
    QDateTime dateTime;     /// 发送时间
    QString sender;     /// 发送者
    QString receiver;   /// 接收者

    MessageBodyPtr messageBody;     /// 消息体

};



/**
 * @brief 聊天消息的消息体
 */
class MessageBody
{
public:
    /**
     * @brief 反序列化数据。从Json字符串转到对象
     * @param jsonString json字符串
     * @return
     * @note 当前基类方法会判断json字符串中的对象类型，
     *      从而调用不同的子类的反序列化函数
     */
    static MessageBodyPtr DeserializationFromJson(const QString &jsonString);
    /**
     * @brief 将对象序列化到字符串
     * @return
     */
    virtual QString serializeToJson() = 0;
    virtual QJsonObject serializeToJsonObject() = 0;

    virtual QString getContent() const = 0;
    virtual void setContent(const QString & value) = 0;
    virtual ~MessageBody() {}


    virtual global::MessageType getType() const = 0;
    virtual void setType(const global::MessageType &value) = 0;
};

/**
 * @brief 文本类型的消息体
 */
class TextMessageBody : public MessageBody
{
public:
    static MessageBodyPtr DeserializationFromJson(const QString &jsonString);
public:
    TextMessageBody(const QString &content, global::MessageType type = global::MessageType::TEXT);
    QString serializeToJson()override;
    QJsonObject serializeToJsonObject()override;
    QString getContent()const override ;
    void setContent(const QString &value)override;

    global::MessageType getType() const override;
    void setType(const global::MessageType &value) override;

private:
    QString content;
    global::MessageType type;
};


/**
 * @brief 图片类型消息体
 */
class ImageMessageBody : public MessageBody
{
public:
    static MessageBodyPtr DeserializationFromJson(const QString &jsonString);
public:
    ImageMessageBody(const QString &content, global::MessageType type = global::MessageType::IMAGE);
    QString serializeToJson()override;
    QJsonObject serializeToJsonObject()override;
    QString getContent() const override;
    void setContent(const QString &value)override;

    global::MessageType getType() const override;
    void setType(const global::MessageType &value) override;

private:
    QString content;            /// 内容
    global::MessageType type;  /// 类型
};

/**
 * @brief 文件类型消息体
 */
class FileMessageBody : public MessageBody
{
public:
    static MessageBodyPtr DeserializationFromJson(const QString &jsonString);
public:
    FileMessageBody(const QString &fileName, const QString &filePath,
                    int fileSize, global::MessageType type = global::MessageType::FILE);
    QString serializeToJson()override;
    QJsonObject serializeToJsonObject()override;

    QString getContent() const override;
    void setContent(const QString &value)override;
    global::MessageType getType() const override;
    void setType(const global::MessageType &value) override;

private:
    QString fileName;       /// 文件名
    QString filePath;       /// 文件路径
    int fileSize;           /// 文件大小
    global::MessageType type;   /// 类型
};


}
#endif // CHATMESSAGERECORD_H
