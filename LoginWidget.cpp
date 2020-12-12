#include "LoginWidget.h"
#include "ui_LoginWidget.h"
#include "Util.h"

#include "ReadQStyleSheet.h"


#include <QDebug>
#include <QApplication>
#include <QSize>
#include <QGraphicsDropShadowEffect>
#include <QMovie>
#include <QColor>


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    initResourceAndForm();
    initSignalsAndSlots();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::mouseMoveEvent(QMouseEvent * e)
{
    QPoint afterMovePos = e->globalPos();
    if(offset.x()!=0&&offset.y()!=0)
    {
        QPoint moveDis = afterMovePos-offset;
        move(moveDis);
    }
}

/*
    鼠标按下事件，按下就获取当前鼠标坐标并计算出当前坐标和窗口左上角的偏移量offset

*/
void LoginWidget::mousePressEvent(QMouseEvent * e)
{

    QPoint currGlobalPos = e->globalPos();              //当前鼠标的全局位置
    QPoint currLocPos = this->geometry().topLeft();    //当前鼠标点击窗口的左上角坐标
    offset = currGlobalPos-currLocPos;
}

/*
    鼠标放开事件，当鼠标放开时，将偏移量offset初始化为0
*/
void LoginWidget::mouseReleaseEvent(QMouseEvent *)
{
    offset = QPoint(0,0);
}

void LoginWidget::initResourceAndForm()
{
    //设置CSS样式
    this->setStyleSheet(ReadQStyleSheet::readQss("://login.css"));
    //设置窗口无标题、窗口在最顶层
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //设置窗口背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);
    //设置外层窗口大小为桌面大小
    QSize desktop = Zsj::getDesktopSize();
    this->setGeometry(0,0,desktop.width(),desktop.height());

    //设置窗口阴影
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);   //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(12);     //阴影的模糊半径
    ui->widgetLogin->setGraphicsEffect(shadow);
    qDebug() << "初始化样式成功";


    ui->comboBoxAccount->addItem("123");
    ui->comboBoxAccount->addItem("456");
    ui->comboBoxAccount->addItem("789");

    QMovie * movie = new QMovie("://res/login/bg-movie.gif");
    ui->labelBgMovie->setMovie(movie);
    movie->start();
    movie->setParent(this);

    //设置控件在背景movie上层   可直接通过设计师界面设计
//    ui->toolButtonClose->raise();
//    ui->toolButtonMin->raise();
//    ui->toolButtonSetting->raise();

    // 设置默认头像
    QPixmap pixmap("://res/login/default-head.png");
    QPixmap round = Zsj::pixmapToRound(pixmap,32);
    ui->labelHeadImage->setPixmap(round);


}

void LoginWidget::initSignalsAndSlots()
{
    connect(ui->toolButtonClose,&QToolButton::clicked,this,&LoginWidget::closeWindow);
    qInfo() << "connect toolButtonClose clicked to LoginWidget::closeWindow";

    connect(ui->toolButtonMin,&QToolButton::clicked,this,[this](){
        QPixmap pixmap = QPixmap("://Z:/default/Pictures/Image/126.jpg");
        QPixmap round = Zsj::pixmapToRound(pixmap,32);
        ui->labelHeadImage->setPixmap(round);
    });
    qInfo() << "connect toolButtonMin clicked to lambda test";
}

void LoginWidget::closeWindow()
{
    this->close();
}
