#include "LinkmanSection.h"
#include "ui_LinkmanSection.h"

LinkmanSection::LinkmanSection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanSection)
{
    ui->setupUi(this);
}

LinkmanSection::LinkmanSection(const QPixmap &icon, const QString &groupName,
                               int active, int total, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanSection)
{
    ui->setupUi(this);

    ui->labelIcon->setPixmap(icon);
    QString group = QString("%1 [%2/%3]").arg(groupName).arg(active).arg(total);
    ui->labelGroupName->setText(group);

    this->groupName = groupName;
}

LinkmanSection::LinkmanSection(const QPixmap &icon,
                               zsj::Section::ptr section,
                               QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanSection),
    section(section)
{
    ui->setupUi(this);
//    QPixmap icon(":/main/res/main/arrow-right.png");
    ui->labelIcon->setPixmap(icon);
    QString group = QString("%1 [%2/%3]")
                    .arg(section->getSectionName())
                    .arg(0).arg(section->getSize());
    ui->labelGroupName->setText(group);

    // 兼容前面的代码
    this->groupName = section->getSectionName();
}

LinkmanSection::~LinkmanSection()
{
    delete ui;
}

void LinkmanSection::setIcon(const QPixmap &icon)
{
    ui->labelIcon->setPixmap(icon);
}

void LinkmanSection::setIcon(const QString &iconPath)
{
    QPixmap icon(iconPath);
    ui->labelIcon->setPixmap(icon);
}

QString LinkmanSection::getGrouoName() const
{
    return groupName;
}

QString LinkmanSection::getSectionName() const
{
    return section->getSectionName();
}
