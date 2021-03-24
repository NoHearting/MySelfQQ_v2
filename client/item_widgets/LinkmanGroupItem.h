/**
  * @brief 联系人界面下的群列表的群子项
  *
  * @author zsj
  * @date 2020年12月23日20:02:20
  */
#pragma once

#include <QWidget>
#include <QPixmap>
#include <QString>

#include "main/GroupData.h"
#include "main/Data.h"

#include "item_widgets/LinkmanItem.h"

namespace Ui {
class LinkmanGroupItem;
}

class LinkmanGroupItem : public LinkmanItem
{
    Q_OBJECT
public:
    LinkmanGroupItem(zsj::GroupData::ptr groupData,const QString & date,QWidget *parent = 0);
    ~LinkmanGroupItem();


    QString getDate() const;
    void setDate(const QString &value);

    zsj::Data::ptr getData()const override;

private:
    /// @brief 设置头像
    void setHead();
private:
    Ui::LinkmanGroupItem *ui;

    /// 群数据
    zsj::GroupData::ptr groupData;

    /// @brief 日期
    QString date;
};

