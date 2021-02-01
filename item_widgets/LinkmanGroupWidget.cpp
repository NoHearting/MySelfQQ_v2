#include "LinkmanGroupWidget.h"
#include "ui_LinkmanGroupWidget.h"

LinkmanGroupWidget::LinkmanGroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanGroupWidget)
{
    ui->setupUi(this);
}

LinkmanGroupWidget::LinkmanGroupWidget(const QPixmap &icon, const QString &groupName,
                                       int active, int total, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanGroupWidget)
{
    ui->setupUi(this);

    ui->labelIcon->setPixmap(icon);
    QString group = QString("%1 [%2/%3]").arg(groupName).arg(active).arg(total);
    ui->labelGroupName->setText(group);

    this->groupName = groupName;
}

LinkmanGroupWidget::~LinkmanGroupWidget()
{
    delete ui;
}

void LinkmanGroupWidget::setIcon(const QPixmap &icon)
{
    ui->labelIcon->setPixmap(icon);
}

void LinkmanGroupWidget::setIcon(const QString &iconPath)
{
    QPixmap icon(iconPath);
    ui->labelIcon->setPixmap(icon);
}

QString LinkmanGroupWidget::getGrouoName() const
{
    return groupName;
}
