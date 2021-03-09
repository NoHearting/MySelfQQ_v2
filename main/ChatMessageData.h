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


    /// 文件类型消息记录
    QString getFilePath()const;
    QString getFileName()const;
    int getFileSize()const;

private:
    QPixmap head;

    /// 当前聊天记录中是否有表情
    bool hasEmoji;

    zsj::ChatMessageRecord chatMessageRecord;
};

}
#endif // CHATMESSAGEDATA_H
