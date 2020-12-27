#include "WarnDialog.h"
#include "ui_WarnDialog.h"
#include "Util.h"
#include "ReadQStyleSheet.h"
#include "Frameless.h"

#include <QDebug>

WarnDialog::WarnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarnDialog)
{
    ui->setupUi(this);
    connect(ui->pushButtonSure,&QPushButton::clicked,this,&WarnDialog::sendSureSignal);
    connect(ui->pushButtonCancel,&QPushButton::clicked,this,&WarnDialog::close);
    connect(ui->toolButtonClose,&QToolButton::clicked,this,&WarnDialog::close);

    ui->pushButtonSure->setFocus();

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);

    zsj::WidgetUtil::setWidgetBoxShadow(this);

    QString qss = zsj::ReadQStyleSheet::readQss("://css/dialog.css");
    this->setStyleSheet(qss);

    zsj::Frameless * frameless = new zsj::Frameless(this);
    frameless->setResizeEnable(false);
    frameless->setWidget(this);
    QPixmap pixmap(":/main/res/main/warn.png");
    changeFlagPng(pixmap);
}

WarnDialog::~WarnDialog()
{
    delete ui;
}

void WarnDialog::showDialog(const QString &title, const QString &info)
{
    if(title.isEmpty()){
        qCritical() << "dialog title is empty,please checked it!";
        return;
    }
    if(info.isEmpty()){
        qCritical() << "dialog info is empty,please checked it!";
        return;
    }
    ui->labelTitle->setText(title);
    ui->labelInfoText->setText(info);
    this->exec();
}

void WarnDialog::changeFlagPng(QPixmap &flag)
{
    if(flag.isNull()){
        qCritical() << "flag Pixmap is null,please checked it!";
        return;
    }
    auto result = zsj::scaledPixmap(flag,54,54);
    ui->labelFlagPng->setPixmap(result);
}

void WarnDialog::sendSureSignal()
{
    emit sure();
}
