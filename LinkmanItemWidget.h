#ifndef LINKMANITEMWIDGET_H
#define LINKMANITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <memory>

#include "UserData.h"

namespace Ui {
class LinkmanItemWidget;
}

class LinkmanItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LinkmanItemWidget(QWidget *parent = 0);

    LinkmanItemWidget(zsj::UserData::ptr userData,QWidget *parent = 0);
    ~LinkmanItemWidget();

    zsj::UserData::ptr getUserData() const;
    void setUserData(const zsj::UserData::ptr value);

private:
    void setHead();

private:
    Ui::LinkmanItemWidget *ui;

    zsj::UserData::ptr userData;
};

#endif // LINKMANITEMWIDGET_H
