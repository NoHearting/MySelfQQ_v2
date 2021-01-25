#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QObject>
#include <QScopedPointer>
#include <QFont>

namespace zsj {



class ChatBubble
{
public:
    static ChatBubble * Instance();
public:
    uint getBubblePadding() const;
    void setBubblePadding(const uint &value);



    QFont getBubbleFont() const;
    void setBubbleFont(const QFont &value);

    int getBubbleFontSize()const;
    void setBubbleFontSize(uint size);

    QString getBubbleFontFamily()const;
    void setBubbleFontFamily(const QString & fontFamily);

private:
    ChatBubble();

    static QScopedPointer<ChatBubble> chatBubble;
private:
    /// 气泡padding
    uint bubblePadding;
    /// 气泡字体
    QFont bubbleFont;
};

}
#endif // CHATBUBBLE_H
