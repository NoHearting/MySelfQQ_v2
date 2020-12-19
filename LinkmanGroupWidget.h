#ifndef LINKMANGROUPWIDGET_H
#define LINKMANGROUPWIDGET_H

#include <QWidget>

namespace Ui {
class LinkmanGroupWidget;
}

class LinkmanGroupWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LinkmanGroupWidget(QWidget *parent = 0);

    LinkmanGroupWidget(const QPixmap & icon,const QString & groupName,int active,int total,QWidget * parent = 0);
    ~LinkmanGroupWidget();


    void setIcon(const QPixmap & icon);
    void setIcon(const QString & iconPath);

private:
    Ui::LinkmanGroupWidget *ui;
};

#endif // LINKMANGROUPWIDGET_H
