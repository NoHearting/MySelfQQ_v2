#include "EmojiInfo.h"


EmojiInfo::EmojiInfo(EmojiType type, const QString &prefix,
                     const QVector<QString> emojiVec) :
    type(type),prefix(prefix),emojiVector(emojiVec),emojiCount(emojiVector.size())
{

}

QString EmojiInfo::toString()
{
    return QString("EmojiInfo:{ prefix:%1,emojiCount:%2,emojiType:%3 }")
            .arg(prefix).arg(emojiCount)
            .arg((type == EmojiType::NORMAL) ? "normal" : "symbol");
}

QString EmojiInfo::getPrefix() const
{
    return prefix;
}

void EmojiInfo::setPrefix(const QString &value)
{
    prefix = value;
}

uint EmojiInfo::getEmojiCount() const
{
    return emojiCount;
}

void EmojiInfo::setEmojiCount(const uint &value)
{
    emojiCount = value;
}


EmojiType EmojiInfo::getType() const
{
    return type;
}

void EmojiInfo::setType(const EmojiType &value)
{
    type = value;
}

QVector<QString> EmojiInfo::getEmojiVector() const
{
    return emojiVector;
}

void EmojiInfo::setEmojiVector(const QVector<QString> &value)
{
    emojiVector = value;
}
