#ifndef LINKMANGROUPITEMWIDGET_H
#define LINKMANGROUPITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QString>

namespace Ui {
class LinkmanGroupItemWidget;
}

class LinkmanGroupItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LinkmanGroupItemWidget(QWidget *parent = 0);
    LinkmanGroupItemWidget(QPixmap & head,const QString & name,const QString & date,QWidget *parent = 0);
    ~LinkmanGroupItemWidget();

private:
    Ui::LinkmanGroupItemWidget *ui;
};

#endif // LINKMANGROUPITEMWIDGET_H
