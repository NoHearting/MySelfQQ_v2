#include "LoginWidget.h"
#include "ui_LoginWidget.h"

#include "ReadQStyleSheet.h"

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    initResourceAndForm();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::initResourceAndForm()
{
    //设置CSS样式
    this->setStyleSheet(ReadQStyleSheet::readQss("://login.css"));
}
