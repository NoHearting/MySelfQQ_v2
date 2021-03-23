#include "LinkmanGroupItem.h"
#include "ui_LinkmanGroupItem.h"
#include "utils/Util.h"


LinkmanGroupItem::LinkmanGroupItem(zsj::GroupData::ptr groupData,
        const QString &date, QWidget *parent) :
    LinkmanItem(parent),
    ui(new Ui::LinkmanGroupItem),
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

LinkmanGroupItem::~LinkmanGroupItem()
{
    delete ui;
}

void LinkmanGroupItem::setHead()
{
    QPixmap head = groupData->getHead();
    QPixmap result = zsj::adjustToHead(head, zsj::HeadSize::linkmanGroupDiameter);
    ui->labelHead->setPixmap(result);
}

QString LinkmanGroupItem::getDate() const
{
    return date;
}

void LinkmanGroupItem::setDate(const QString &value)
{
    date = value;
}

zsj::Data::ptr LinkmanGroupItem::getData() const
{
    return groupData;
}


