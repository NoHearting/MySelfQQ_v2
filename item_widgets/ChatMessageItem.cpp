#include "ChatMessageItem.h"

#include <QString>
#include <QFontMetrics>
#include <QDebug>
#include <QRegExp>

#include "main/ChatBubble.h"

namespace zsj
{


ChatMessageItem::ChatMessageItem()
{

}

ChatMessageItem::~ChatMessageItem()
{

}

int ChatMessageItem::getContentMaxWidth(const QString &content, const int currWidth,
                                        int &enterCount, const QFontMetrics &fm)
{
    /// @note 思考过于狭窄，只考虑了p标签。有可能不存在p标签
//    const QString extraString = "<p></p>";
//    int maxWidth = 0;
//    int index = 0;
//    enterCount = 0;
//    do
//    {
//        int begin = content.indexOf("<p>",index);
//        if(begin == -1){
//            break;
//        }
//        int end = content.indexOf("</p>",begin);
//        if(-1 == begin){
//            break;
//        }
//        QString temp = content.mid(begin,end-begin + 4);

//        int hasEmoji = false;
//        int imgIndex = temp.indexOf("<img");
//        if(-1 != imgIndex){
//            int endImgIndex = temp.indexOf("/>",imgIndex);
//            QString imgSrc = temp.mid(imgIndex,endImgIndex - imgIndex + 2);
//            temp.replace(imgSrc,"");
//            hasEmoji = true;
//        }

//        int width = fm.horizontalAdvance(temp) - fm.horizontalAdvance(extraString);
//        if(hasEmoji){
//            width += (zsj::ChatBubble::EmojiChatSize * 1.2);
//        }
//        if(width > currWidth - 90){
//            maxWidth = currWidth - 90;
//            int line = width / (currWidth - 90);
//            int lineRemain  = width % (currWidth - 90);
//            enterCount += (lineRemain ? line : line + 1);
//        }
//        else if(width > maxWidth){
//            maxWidth = width;
//        }
//        // 有问题
////        enterCount++;
//        index = end + 4;
//    }
//    while(index < content.size());
//    return maxWidth;

    int maxWidth = 0;
    int index = 0;
    enterCount = 0;
    bool onlyLine = true;

    do
    {
        int pos = content.indexOf("\n", index);
        if(-1 == pos && !onlyLine)
        {
            break;
        }
        else if(-1 == pos && onlyLine){
            pos = content.size();
            onlyLine = false;
        }
        QString line = content.mid(index, pos - index);
        if(line.size() < 1){
            break;
        }
        int width = getTagContentWidth(line, fm);
        if(width > currWidth - 90)
        {
            maxWidth = currWidth - 90;
            int line = width / (currWidth - 90);
            int lineRemain  = width % (currWidth - 90);
            enterCount += (lineRemain ? line : line + 1);
        }
        else if(width > maxWidth)
        {
            maxWidth = width;
        }
        enterCount++;
        index = pos+1;
    }
    while(index != -1 &&index < content.size());
    if(enterCount > 30){
        enterCount += enterCount * 0.07;
    }
    return maxWidth;

}

int ChatMessageItem::getTagContentWidth(const QString &content, const QFontMetrics &fm)
{
    QRegExp rx("(</?\\w{0,10}>)");
    QString tagList;
    int pos = 0;

    while ((pos = rx.indexIn(content, pos)) != -1) {
        tagList.append(rx.cap(1));
        pos += rx.matchedLength();
    }
    pos = 0;
    int emojiCount = 0;
    QString temp = content;
    do{
        int begin = content.indexOf("<img",pos);
        if(-1 == begin){
            break;
        }
        int end = content.indexOf("/>",begin);
        if(-1 == end){
            break;
        }
        QString imgTag = content.mid(begin,end - begin + 2);
        temp.replace(imgTag,"");
        emojiCount++;
        pos = end;
    }while(pos!=-1 && pos < content.size());
    int width = fm.horizontalAdvance(temp) - fm.horizontalAdvance(tagList);
    if(emojiCount>0){
        width += (zsj::ChatBubble::EmojiChatSize * 1.2) * emojiCount;
    }
    return width;
}


}
