/**
  * @file ChatMessageImageItemObject.h
  * @brief 消息列表中的消息类型。纯图片类型，用于显示图片
  * @author zsj
  * @date 2021年3月2日09:22:59
  * @note 只用于显示图片。后续可以改进
  */
#ifndef CHATMESSAGEIMAGEITEMOBJECT_H
#define CHATMESSAGEIMAGEITEMOBJECT_H

#include <QWidget>
#include <QString>
#include <QListWidget>

#include "item_widgets/ChatMessageItem.h"
#include "main/ChatMessageData.h"

namespace Ui {
class ChatMessageImageItemObject;
}

class ChatMessageImageItemObject : public QWidget,public zsj::ChatMessageItem
{
    Q_OBJECT

public:
    explicit ChatMessageImageItemObject(QWidget *parent = nullptr);
    ChatMessageImageItemObject(zsj::ChatMessageData::ptr data,QListWidgetItem * item,
                               QWidget * parent = nullptr);
    ~ChatMessageImageItemObject();

    void adjustWidgetsPosition() override;
    QSize calculateMessageWidgetSize() override;
    QSize getWidgetSize()override;

    /**
     * @brief 每一次item变化后就需要重新贴图
     */
    void adjustImage();
protected:
    void resizeEvent(QResizeEvent *event);

private:

    void initResourceAndForm();

    /**
     * @brief 获取当前可显示的图片大小
     * @param windowSize 当前窗口大小
     * @return
     */
    QSize currentEnableImageSize(QSize windowSize);

    /**
     * @brief 将img标签中的src属性的值取出来
     * @param imgTag 形如<img src="src" />
     * @return
     */
    QString seprateImageSrc(const QString & imgTag);
private:
    Ui::ChatMessageImageItemObject *ui;

    QListWidgetItem * item;

    /// 聊天对象的数据
    zsj::ChatMessageData::ptr chatMessageData;


    /// 显示的图片呢
    QPixmap image;
};

#endif // CHATMESSAGEIMAGEITEMOBJECT_H
