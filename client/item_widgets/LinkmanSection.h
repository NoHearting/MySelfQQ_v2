/**
  * @brief 联系人界面下的群列表、好友列表的分组项
  *
  * @author zsj
  * @date 2020年12月23日20:04:17
  */
#ifndef LINKMANSECTION_H
#define LINKMANSECTION_H

#include <QWidget>

#include "main/Section.h"

namespace Ui {
class LinkmanSection;
}

class LinkmanSection : public QWidget
{
    Q_OBJECT

public:
    explicit LinkmanSection(QWidget *parent = 0);

    LinkmanSection(const QPixmap & icon,const QString & groupName,int active,int total,QWidget * parent = 0);
    LinkmanSection(const QPixmap & icon,zsj::Section::ptr section,QWidget * parent = 0);
    ~LinkmanSection();


    /// @brief 设置分组项的前置图标
    /// @param[in] icon 图标
    void setIcon(const QPixmap & icon);

    /// @brief 设置分组项的前置图标
    /// @param[in] iconPath 图标路径
    void setIcon(const QString & iconPath);


    QString getGrouoName()const;

    QString getSectionName()const;

    quint64 getSectionId()const{return section->getId();}
private:
    Ui::LinkmanSection *ui;


    QString groupName;

    zsj::Section::ptr section;
};

#endif // LINKMANSECTION_H
