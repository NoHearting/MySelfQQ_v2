#include "LinkmanItemWidget.h"
#include "ui_LinkmanItemWidget.h"
#include "Util.h"

#include <QDebug>
#include <QPoint>

LinkmanItemWidget::LinkmanItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanItemWidget)
{
    ui->setupUi(this);
}

LinkmanItemWidget::LinkmanItemWidget(QPixmap &head, const QString &nickname,
                                     const QString &remark, const QString &signature,
                                     QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanItemWidget)
{
    ui->setupUi(this);
    QPixmap round = Zsj::adjustToHead(head,Zsj::HeadSize::linkmanItemWidth);
    ui->labelHead->setPixmap(round);
    ui->labelNickname->setText(nickname);
    ui->labelRemark->setText(remark);
    ui->labelSignature->setText(signature);

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

void LinkmanItemWidget::setHead(const QPixmap &head)
{
    ui->labelHead->setPixmap(head);
}

void LinkmanItemWidget::setHead(const QString &headPath)
{
    QPixmap head(headPath);
    ui->labelHead->setPixmap(head);
}

void LinkmanItemWidget::setNickname(const QString &nickname)
{
    ui->labelNickname->setText(nickname);
}

void LinkmanItemWidget::setRemark(const QString &remark)
{
    ui->labelRemark->setText(remark);
}

void LinkmanItemWidget::setSignature(const QString &signature)
{
    ui->labelSignature->setText(signature);
}
