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

namespace Ui {
class MessageItemWidget;
}


enum class DataType{
    USER_DATA = 0,
    GROUP_DATA = 1,
    SYSTEM_DATA = 2
};

class MessageItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageItemWidget(QWidget *parent = 0);
    MessageItemWidget(QPixmap & head,const QString & nickname,const QString & message,
                      const QString & date,bool symbol = false,bool globalInform = false,
                      DataType type = DataType::USER_DATA,QWidget *parent = 0);

    ~MessageItemWidget();

    DataType getType() const;
    void setType(const DataType &value);

protected:
    void resizeEvent(QResizeEvent *);

private:
    void initPosition();
    void updatePosition();

private:
    Ui::MessageItemWidget *ui;

    DataType type;      /// 数据类型
};

#endif // MESSAGEITEMWIDGET_H
