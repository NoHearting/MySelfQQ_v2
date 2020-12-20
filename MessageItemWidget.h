#ifndef MESSAGEITEMWIDGET_H
#define MESSAGEITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QString>

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
                      QWidget *parent = 0);

    ~MessageItemWidget();

protected:
    void resizeEvent(QResizeEvent *);

private:
    void initPosition();
    void updatePosition();

private:
    Ui::MessageItemWidget *ui;
};

#endif // MESSAGEITEMWIDGET_H
