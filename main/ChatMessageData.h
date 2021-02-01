#ifndef CHATMESSAGEDATA_H
#define CHATMESSAGEDATA_H


#include <QPixmap>
#include <QString>

#include <QSharedPointer>

namespace zsj {

class ChatMessageData
{
public:
    typedef QSharedPointer<ChatMessageData> ptr;
    ChatMessageData();
    ChatMessageData(QPixmap &head, const QString &message);


    QPixmap getHead() const;
    void setHead(const QPixmap &value);

    QString getMessage() const;
    void setMessage(const QString &value);

private:
    QPixmap head;
    QString message;
};

}
#endif // CHATMESSAGEDATA_H
