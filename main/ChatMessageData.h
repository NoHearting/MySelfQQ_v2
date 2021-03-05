#ifndef CHATMESSAGEDATA_H
#define CHATMESSAGEDATA_H


#include <QPixmap>
#include <QString>

#include <QSharedPointer>

#include "main/ChatMessageRecord.h"

namespace zsj {

class ChatMessageData
{
public:
    typedef QSharedPointer<ChatMessageData> ptr;
    ChatMessageData();


    /**
     * @brief 组装用于item显示必须的数据
     * @param head 头像
     * @param chatMessageRecord 聊天记录
     */
    ChatMessageData(QPixmap & head,const zsj::ChatMessageRecord & chatMessageRecord);

//    /**
//     * @brief 用于构建显示图片的item
//     * @param imagePath 图片路径
//     * @param head 头像
//     */
//    ChatMessageData(const QString &imagePath,QPixmap &head);

//    /**
//     * @brief 用于构建显示消息的item
//     * @param head 头像
//     * @param message 消息
//     * @param hasEmoji 消息中是否含有表情
//     */
//    ChatMessageData(QPixmap &head, const QString &message,bool hasEmoji = false);


    QPixmap getHead() const;
    void setHead(const QPixmap &value);

    QString getMessage() const;
    void setMessage(const QString &value);


    bool getHasEmoji() const;
    void setHasEmoji(bool value);




    QString getImagePath() const;
    void setImagePath(const QString &value);

    zsj::ChatMessageRecord getChatMessageRecord() const;
    void setChatMessageRecord(const zsj::ChatMessageRecord &value);

private:
    QPixmap head;
    //    QString message;
    //    QString imagePath;

    /// 当前聊天记录中是否有表情
    bool hasEmoji;

    zsj::ChatMessageRecord chatMessageRecord;
};

}
#endif // CHATMESSAGEDATA_H
