/**
  * @file EmojiInfo.h
  * @brief 表情信息类。用于返回文件夹中的表情信息
  * @date 2021年2月21日13:50:31
  * @author zsj
  */
#ifndef EMOJIDATA_H
#define EMOJIDATA_H


#include <QString>
#include <QVector>

enum class EmojiType{
    NORMAL,     /// 经典表情
    SYMBOL      /// 符号表情
};

class EmojiInfo
{
public:
    EmojiInfo(){}

    EmojiInfo(EmojiType type,const QString & prefix,const QVector<QString> emojiVec);


    QString toString();

    QString getPrefix() const;
    void setPrefix(const QString &value);

    uint getEmojiCount() const;
    void setEmojiCount(const uint &value);


    EmojiType getType() const;
    void setType(const EmojiType &value);

    QVector<QString> getEmojiVector() const;
    void setEmojiVector(const QVector<QString> &value);

private:

    /// 表情在项目资源文件的前缀
    QString prefix;

    /// 所有表情的 qrc路径
    QVector<QString> emojiVector;

    /// 表情的数目
    uint emojiCount;

    /// 当前所有表情的分类
    EmojiType type;

};

#endif // EMOJIDATA_H
