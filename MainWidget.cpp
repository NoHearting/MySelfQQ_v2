#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "ReadQStyleSheet.h"


#include <QDebug>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    initObjects();
    initResourceAndForm();
    initSignalsAndSlots();
}

MainWidget::~MainWidget()
{
    delete ui;
}



void MainWidget::initObjects()
{

}

void MainWidget::closeWindow()
{
    qApp->quit();
}

void MainWidget::minWindow()
{
    this->hide();
}

void MainWidget::initResourceAndForm()
{
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    frameless = new Zsj::Frameless(this);
    frameless->setWidget(this);      //设置窗口可移动，可扩展

    systemTray = new Zsj::SystemTray(this);

    systemTray->showSystemTray();
    QPixmap * trayIcon = new QPixmap(":/global/res/global/water-tray.png");
    systemTray->setSystemTrayIcon(trayIcon);
    this->setStyleSheet(Zsj::ReadQStyleSheet::readQss("://css/main.css"));


    //设置窗口阴影
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);   //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(12);     //阴影的模糊半径
    ui->widgetMain->setGraphicsEffect(shadow);
}

void MainWidget::initSignalsAndSlots()
{
    connect(ui->toolButtonClose,&QToolButton::clicked,this,&MainWidget::closeWindow);
    qInfo() << "connect QToolButton::clicked to MainWidget::closeWindow";

    connect(ui->toolButtonMin,&QToolButton::clicked,this,&MainWidget::minWindow);
    qInfo() << "connect toolButtonMin::clicked to MainWidget::minWindow";

    connect(systemTray,&Zsj::SystemTray::sigOpenWindow,this,&MainWidget::show);
    qInfo() << "connect systemTray::sigOpenWindow to MainWidget::show";

}
