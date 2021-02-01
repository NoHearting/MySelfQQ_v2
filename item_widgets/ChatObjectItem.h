#ifndef CHATOBJECTITEM_H
#define CHATOBJECTITEM_H

#include <QWidget>
#include <QResizeEvent>
#include <QPoint>
#include <QRect>

#include "main/Data.h"

namespace Ui {
class ChatObjectItem;
}

class ChatObjectItem : public QWidget
{
    Q_OBJECT

public:
    explicit ChatObjectItem(zsj::Data::ptr data,QWidget *parent = nullptr);
    ~ChatObjectItem();
    zsj::Data::ptr getData() const;

    /// @brief 获取删除按钮的位置和大小
    /// @return QRect
    QRect getDeleteButtonPosition() const;

    int getIndex() const;

protected:

    void resizeEvent(QResizeEvent *);

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    void init();

    /// @brief 设置QLabel适应文字大小
    void adjustLabelText();

    /// @brief 设置QLabel的位置
    void adjustLabelPostion();

    /// @brief 初始化样式
    void initStyleSheet();


private:
    Ui::ChatObjectItem *ui;

    zsj::Data::ptr data;

public slots:
    void slotDeleteItem();
signals:

    void sigDeleteItem(QPoint pos);

};

#endif // CHATOBJECTITEM_H
