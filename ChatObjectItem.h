#ifndef CHATOBJECTITEM_H
#define CHATOBJECTITEM_H

#include <QWidget>
#include <QResizeEvent>

#include "Data.h"

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

protected:
    void resizeEvent(QResizeEvent *);

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

};

#endif // CHATOBJECTITEM_H
