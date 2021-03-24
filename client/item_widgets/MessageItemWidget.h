/**
  * @brief 消息界面的消息列表的消息子项
  *
  * @author zsj
  * @date 2020年12月23日20:13:43
  */
#ifndef MESSAGEITEMWIDGET_H
#define MESSAGEITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QDateTime>

#include "utils/Global.h"

#include "main/Data.h"

namespace Ui {
class MessageItemWidget;
}



class MessageItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageItemWidget(QWidget *parent = 0);
    MessageItemWidget(QPixmap & head,const QString & nickname,const QString & message,
                      const QString & date,bool symbol = false,bool globalInform = false,
                      zsj::global::DataType type = zsj::global::DataType::USER_DATA,QWidget *parent = 0);

    MessageItemWidget(const zsj::Data::ptr data,QWidget * parent = nullptr);

    ~MessageItemWidget();

    zsj::global::DataType getType() const;
    void setType(const zsj::global::DataType &value);

    QString getNickname()const;



    void setMessage(const QString & msg);
    void setDateTime(const QDateTime & dateTime = QDateTime::currentDateTime());
    zsj::Data::ptr getData() const;
    void setData(const zsj::Data::ptr &value);

protected:
    void resizeEvent(QResizeEvent *);

private:
    void initPosition();
    void updatePosition();

private:
    Ui::MessageItemWidget *ui;

    zsj::global::DataType type;      /// 数据类型   delete
    zsj::Data::ptr data;
};

#endif // MESSAGEITEMWIDGET_H
