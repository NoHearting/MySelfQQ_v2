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

    /// 气泡、聊天输入框字体大小
    static const uint FontSize = 18;
    /// 聊天输入框的表情大小
    static const uint EmojiInputSize = 28;
    /// 消息列表的表情大小
    static const uint EmojiChatSize = 22;
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
