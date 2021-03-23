#include "LinkmanUserItem.h"
#include "ui_LinkmanUserItem.h"
#include "utils/Util.h"

#include <QDebug>
#include <QPoint>
#include <memory>

LinkmanUserItem::LinkmanUserItem(zsj::UserData::ptr data,
                                     QWidget *parent) :
    LinkmanItem(parent),
    ui(new Ui::LinkmanUserItem),
    userData(data)
{
    ui->setupUi(this);

    setHead();

    ui->labelNickname->setText(this->userData->getName());
    ui->labelRemark->setText(this->userData->getRemark());
    ui->labelSignature->setText(this->userData->getExplain());

    ui->labelNickname->adjustSize();
    QPoint begin = ui->labelNickname->pos() + QPoint(ui->labelNickname->size().width() + 5,0);

    ui->labelRemark->adjustSize();
    ui->labelRemark->setGeometry(begin.x(),begin.y(),ui->labelRemark->width(),ui->labelRemark->height());
    ui->labelSignature->adjustSize();
}

LinkmanUserItem::~LinkmanUserItem()
{
    delete ui;
}

void LinkmanUserItem::setHead(){
    QPixmap head = userData->getHead();
    QPixmap result = zsj::adjustToHead(head,zsj::HeadSize::linkmanItemDiameter);
    ui->labelHead->setPixmap(result);
}

zsj::Data::ptr LinkmanUserItem::getData() const
{
    return userData;
}

