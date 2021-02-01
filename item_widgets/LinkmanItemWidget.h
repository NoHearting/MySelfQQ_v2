/**
  * @brief 联系人界面下联系人列表的列表项
  *
  * @author zsj
  * @date 2020年12月23日20:06:14
  */
#ifndef LINKMANITEMWIDGET_H
#define LINKMANITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <memory>

#include "main/UserData.h"

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
    /// @brief 设置头像
    void setHead();

private:
    Ui::LinkmanItemWidget *ui;

    /// 用户数据
    zsj::UserData::ptr userData;
};

#endif // LINKMANITEMWIDGET_H
