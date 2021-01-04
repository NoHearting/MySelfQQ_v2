#include "LinkmanGroupItemWidget.h"
#include "ui_LinkmanGroupItemWidget.h"
#include "Util.h"

LinkmanGroupItemWidget::LinkmanGroupItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanGroupItemWidget),
    groupData(zsj::GroupData::ptr(new zsj::GroupData))
{
    ui->setupUi(this);
}

LinkmanGroupItemWidget::LinkmanGroupItemWidget(zsj::GroupData::ptr groupData,
        const QString &date, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanGroupItemWidget),
    groupData(groupData)
{
    ui->setupUi(this);

    setHead();
    ui->labelNickname->setText(groupData->getName());
    ui->labelDate->setText(date);
    this->date = date;

    ui->labelNickname->adjustSize();
    ui->labelDate->setText(date);
}

LinkmanGroupItemWidget::~LinkmanGroupItemWidget()
{
    delete ui;
}

void LinkmanGroupItemWidget::setHead()
{
    QPixmap head = groupData->getHead();
    QPixmap result = zsj::adjustToHead(head, zsj::HeadSize::linkmanGroupDiameter);
    ui->labelHead->setPixmap(result);
}

QString LinkmanGroupItemWidget::getDate() const
{
    return date;
}

void LinkmanGroupItemWidget::setDate(const QString &value)
{
    date = value;
}

zsj::GroupData::ptr LinkmanGroupItemWidget::getGroupData() const
{
    return groupData;
}

void LinkmanGroupItemWidget::setGroupData(const zsj::GroupData::ptr &value)
{
    groupData = value;
}
