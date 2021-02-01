/**
  * @brief 联系人界面下的群列表的群子项
  *
  * @author zsj
  * @date 2020年12月23日20:02:20
  */
#ifndef LINKMANGROUPITEMWIDGET_H
#define LINKMANGROUPITEMWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QString>

#include "main/GroupData.h"

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



    zsj::GroupData::ptr getGroupData() const;
    void setGroupData(const zsj::GroupData::ptr &value);

    QString getDate() const;
    void setDate(const QString &value);

private:
    /// @brief 设置头像
    void setHead();
private:
    Ui::LinkmanGroupItemWidget *ui;

    /// 群数据
    zsj::GroupData::ptr groupData;

    /// @brief 日期
    QString date;
};

#endif // LINKMANGROUPITEMWIDGET_H
