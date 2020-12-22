#ifndef LINKMANGROUPITEMWIDGET_H
#define LINKMANGROUPITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QString>

#include "GroupData.h"

namespace Ui {
class LinkmanGroupItemWidget;
}

class LinkmanGroupItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LinkmanGroupItemWidget(QWidget *parent = 0);
    LinkmanGroupItemWidget(zsj::GroupData::ptr groupData,const QString & date,QWidget *parent = 0);
    ~LinkmanGroupItemWidget();

private:
    void setHead();
private:
    Ui::LinkmanGroupItemWidget *ui;

    zsj::GroupData::ptr groupData;
};

#endif // LINKMANGROUPITEMWIDGET_H
