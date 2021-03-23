/**
  * @brief 联系人界面下联系人列表的列表项
  *
  * @author zsj
  * @date 2020年12月23日20:06:14
  */
#pragma once

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <memory>

#include "main/Data.h"
#include "item_widgets/LinkmanItem.h"
#include "main/UserData.h"

namespace Ui
{
class LinkmanUserItem;
}

class LinkmanUserItem : public LinkmanItem
{
    Q_OBJECT

public:

    LinkmanUserItem(zsj::UserData::ptr data, QWidget *parent = 0);
    ~LinkmanUserItem();

    zsj::Data::ptr getData()const override;

private:
    /// @brief 设置头像
    void setHead();



private:
    Ui::LinkmanUserItem *ui;

    /// 用户数据
    zsj::UserData::ptr userData;

};

