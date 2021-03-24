#include "ChatBubble.h"


#include <QMutex>
#include <QMutexLocker>

namespace zsj {


QScopedPointer<ChatBubble> ChatBubble::chatBubble;

ChatBubble::ChatBubble()
{
    bubblePadding = 9;
    bubbleFont = QFont("微软雅黑",FontSize);
    bubbleFont.setPixelSize(FontSize);
}

QFont ChatBubble::getBubbleFont() const
{
    return bubbleFont;
}

void ChatBubble::setBubbleFont(const QFont &value)
{
    bubbleFont = value;
}

int ChatBubble::getBubbleFontSize() const
{
    return bubbleFont.pixelSize();
}

void ChatBubble::setBubbleFontSize(uint size)
{
    bubbleFont.setPixelSize(size);
}

QString ChatBubble::getBubbleFontFamily() const
{
    return bubbleFont.family();
}

void ChatBubble::setBubbleFontFamily(const QString &fontFamily)
{
    bubbleFont.setFamily(fontFamily);
}

ChatBubble *ChatBubble::Instance()
{
    if(chatBubble.isNull()){
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if(chatBubble.isNull()){
            chatBubble.reset(new ChatBubble);
        }
    }
    return chatBubble.data();
}

uint ChatBubble::getBubblePadding() const
{
    return bubblePadding;
}

void ChatBubble::setBubblePadding(const uint &value)
{
    bubblePadding = value;
}
}
