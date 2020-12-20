#include "LinkmanGroupItemWidget.h"
#include "ui_LinkmanGroupItemWidget.h"
#include "Util.h"

LinkmanGroupItemWidget::LinkmanGroupItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanGroupItemWidget)
{
    ui->setupUi(this);
}

LinkmanGroupItemWidget::LinkmanGroupItemWidget(QPixmap &head, const QString &name,
                                               const QString &date, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LinkmanGroupItemWidget)
{
    ui->setupUi(this);

    QPixmap round = Zsj::adjustToHead(head,Zsj::HeadSize::linkmanGroupWidth);
    ui->labelHead->setPixmap(round);
    ui->labelNickname->setText(name);
    ui->labelDate->setText(date);

    ui->labelNickname->adjustSize();
    ui->labelDate->setText(date);
}

LinkmanGroupItemWidget::~LinkmanGroupItemWidget()
{
    delete ui;
}
