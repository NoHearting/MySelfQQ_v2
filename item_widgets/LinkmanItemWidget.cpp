#include "LinkmanItemWidget.h"
#include "ui_LinkmanItemWidget.h"
#include "utils/Util.h"

#include <QDebug>
#include <QPoint>
#include <memory>

LinkmanItemWidget::LinkmanItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanItemWidget),
    userData(zsj::UserData::ptr(new zsj::UserData))
{
    ui->setupUi(this);

}

LinkmanItemWidget::LinkmanItemWidget(zsj::UserData::ptr userData,
                                     QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanItemWidget),
    userData(userData)
{
    ui->setupUi(this);

    setHead();

    ui->labelNickname->setText(this->userData->getNickname());
    ui->labelRemark->setText(this->userData->getRemark());
    ui->labelSignature->setText(this->userData->getSignature());

    ui->labelNickname->adjustSize();
    QPoint begin = ui->labelNickname->pos() + QPoint(ui->labelNickname->size().width() + 5,0);

    ui->labelRemark->adjustSize();
    ui->labelRemark->setGeometry(begin.x(),begin.y(),ui->labelRemark->width(),ui->labelRemark->height());
    ui->labelSignature->adjustSize();
}

LinkmanItemWidget::~LinkmanItemWidget()
{
    delete ui;
}

void LinkmanItemWidget::setHead(){
    QPixmap head = userData->getHead();
    QPixmap result = zsj::adjustToHead(head,zsj::HeadSize::linkmanItemDiameter);
    ui->labelHead->setPixmap(result);
}

zsj::UserData::ptr LinkmanItemWidget::getUserData() const
{
    return userData;
}

void LinkmanItemWidget::setUserData(const zsj::UserData::ptr value)
{
    userData = value;
}
