#include "LoginWidget.h"
#include "ui_LoginWidget.h"
#include "utils/Util.h"

#include "main/ReadQStyleSheet.h"
#include "main/Frameless.h"


#include <QDebug>
#include <QApplication>
#include <QSize>
#include <QGraphicsDropShadowEffect>
#include <QMovie>
#include <QColor>
#include <QAbstractItemView>
#include <QtMath>
#include <QScrollBar>
#include <QRect>
#include <QTimer>


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    initObjects();
    initResourceAndForm();
    initSignalsAndSlots();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

//// 含有一个移动bug
//// 当打开比如下拉框、菜单的东西时，点击桌面（不点击下拉框和菜单），此时移动鼠标到窗口，
//// 窗口会突然非法移动
//void LoginWidget::mouseMoveEvent(QMouseEvent * e)
//{
//    QPoint afterMovePos = e->globalPos();
//    if(offset.x()!=0&&offset.y()!=0)
//    {
//        QPoint moveDis = afterMovePos-offset;
//        move(moveDis);
//    }
//}

/// *
//    鼠标按下事件，按下就获取当前鼠标坐标并计算出当前坐标和窗口左上角的偏移量offset

//    含有一个移动bug
//    当打开比如下拉框、菜单的东西时，点击桌面（不点击下拉框和菜单），此时移动鼠标到窗口，
//    窗口会突然非法移动

//    原因：
//    由于该移动算法是基于窗口的geometry左上角pos和全局鼠标pos的差值offset来实现移动窗口
//    当出现下拉框、菜单时，单击桌面也会被mousePressEvent所捕获，所以记录了一个错误的offset
//    当鼠标再次碰到窗口时，就会非法移动

//    解决办法：
//    先计算出当前主窗口的位置大小QRect，当捕获到点击事件时，判断鼠标的位置是否在主窗口的矩形内，
//    如果在则记录offset，不在则不做任何操作
//*/
//void LoginWidget::mousePressEvent(QMouseEvent * e)
//{
//    QPoint topLeft = ui->widgetLoginTop->mapToGlobal(ui->widgetLoginTop->pos()) - QPoint(0,130);
//    QRect realGeometry(topLeft,QSize(ui->widgetLogin->size()));  // 当前窗口的真实位置大小
//    QPoint cursorPos = e->globalPos();              //当前鼠标的全局位置
//    if(realGeometry.contains(cursorPos)){
//        QPoint geometryTopLeft = this->geometry().topLeft();    //当前鼠标点击窗口的左上角坐标
//        offset = cursorPos-geometryTopLeft;
//    }
//}

/// *
//    鼠标放开事件，当鼠标放开时，将偏移量offset初始化为0
//*/
//void LoginWidget::mouseReleaseEvent(QMouseEvent *)
//{
//    offset = QPoint(0,0);
//}


void LoginWidget::initObjects()
{
    // 组合框
    comboBoxListWidget = new QListWidget(this);

    // 初始化系统托盘
    systemTray = new zsj::SystemTray(this);
    systemTray->showSystemTray();  //显示

    toolTip = new ToolTipWidget(this);

    frameless = new zsj::Frameless(this);
    frameless->setResizeEnable(false);
}

void LoginWidget::initResourceAndForm()
{
    //设置CSS样式
    this->setStyleSheet(zsj::ReadQStyleSheet::readQss("://css/login.css"));
    // 窗口的属性
    // Qt::Tool 窗口不再任务栏显示
    // Qt::WindowStaysOnTopHint 窗口在最顶层
    // Qt::FramelessWindowHint  窗口无标题栏
    // Qt::WindowSystemMenuHint 允许任务栏按钮右键菜单
    // Qt::WindowMinimizeButtonHint 允许最小化和还原
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    //设置窗口背景透明
    this->setAttribute(Qt::WA_TranslucentBackground);

    //设置窗口阴影
    QGraphicsDropShadowEffect * shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0,0);   //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(12);     //阴影的模糊半径
    ui->widgetLogin->setGraphicsEffect(shadow);
    qDebug() << "初始化样式成功";


    QMovie * movie = new QMovie("://res/login/bg-movie.gif");
    ui->labelBgMovie->setMovie(movie);
    ui->labelBgMovieLogin->setMovie(movie);
    movie->start();
    movie->setParent(this);

    // 设置默认头像
    QPixmap pixmap("://res/login/default-head.png");
    head = zsj::pixmapToRound(pixmap,32);
    ui->labelHeadImage->setPixmap(head);
    ui->labelHeadImageLogin->setPixmap(head);


    comboBoxListWidget->setFixedHeight(180);
    comboBoxListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->comboBoxAccount->setModel(comboBoxListWidget->model());
    ui->comboBoxAccount->setView(comboBoxListWidget);
    ui->comboBoxAccount->setMaxVisibleItems(3);         //配合CSS显示下拉框正确高度

    // 将视图的父窗口设置为透明的，目的是让QComboBox的下拉框透明  需要配合css
    ui->comboBoxAccount->view()->parentWidget()->setWindowFlags(Qt::Popup|Qt::FramelessWindowHint);
    ui->comboBoxAccount->view()->parentWidget()->setAttribute(Qt::WA_TranslucentBackground);


    for(int i = 0;i<5;i++){
        QString head = QString(":/test/Z:/default/Pictures/head/head%1.jpg").arg(i);
        QPixmap origin(head);
        QPixmap scaled = zsj::scaledPixmap(origin,40,40);
        QPixmap round = zsj::pixmapToRound(scaled,20);
        ComboBoxItemWidget * item = new ComboBoxItemWidget(round,
                                                           QString("无心-%1").arg(i),
                                                           "123512341",
                                                           "asda123",this);

        item->setFixedSize(235,50);
        QListWidgetItem * widgetItem = new QListWidgetItem(comboBoxListWidget);
        connect(item,&ComboBoxItemWidget::click,this,&LoginWidget::setAccountAndPassword);
        qInfo() << "connect ComboBoxItemWidget click to LoginWidget::setAccountAndPassword";
        comboBoxListWidget->setItemWidget(widgetItem,item);
        widgetItem->setSizeHint(QSize(235,50));
    }


}

void LoginWidget::initSignalsAndSlots()
{
    connect(ui->toolButtonClose,&QToolButton::clicked,this,&LoginWidget::closeWindow);
    connect(ui->toolButtonCloseLogin,&QToolButton::clicked,this,&LoginWidget::closeWindow);
    connect(ui->toolButtonCloseLoginError,&QToolButton::clicked,this,&LoginWidget::closeWindow);
    qInfo() << "connect toolButtonClose clicked to LoginWidget::closeWindow";

    connect(ui->pushButtonDropDown,&QPushButton::clicked,this,&LoginWidget::showComboBoxPopus);
    qInfo() << "connect QPushButton cliecked to LoginWidget::showComboBoxPopus";

    connect(ui->comboBoxAccount,&MyComboBox::setLineEditCssOn,this,[=](){
        ui->lineEditOuterInput->setStyleSheet("#lineEditOuterInput{border-bottom:1px solid rgb(18,183,245);"
                                           "background:left top no-repeat url('://res/login/logo2.png');}");
        ui->pushButtonDropDown->setStyleSheet("background:url('://res/login/arrow-on.png');");
    });
    qInfo() << "connect MyComboBox::setLineEditCssOn to lambda func to set css";

    connect(ui->comboBoxAccount,&MyComboBox::setLineEditCssOff,this,[=](){
        ui->lineEditOuterInput->setStyleSheet("#lineEditOuterInput{border-bottom:1px solid rgb(229,229,229);"
                                              "background:left top no-repeat url('://res/login/logo1.png');}"
                                              "#lineEditOuterInput:hover{border-bottom:1px solid rgb(193,193,193);}"
                                              "#lineEditOuterInput:focus{border-bottom:1px solid rgb(18,183,245);"
                                              "background:left top no-repeat url('://res/login/logo2.png');}");
        ui->pushButtonDropDown->setStyleSheet("#pushButtonDropDown{background:url('://res/login/arrow.png');}"
                                              "#pushButtonDropDown:hover{background:url('://res/login/arrow-hover.png');}");
        ui->comboBoxAccount->view()->verticalScrollBar()->setSliderPosition(0);  // 将滚动条复位
    });
    qInfo() << "connect MyComboBox::setLineEditCssOff to lambda func to set css";


    connect(ui->toolButtonMin,&QToolButton::clicked,this,&LoginWidget::minWindow);
    connect(ui->toolButtonMinLogin,&QToolButton::clicked,this,&LoginWidget::minWindow);
    connect(ui->toolButtonMinLoginError,&QToolButton::clicked,this,&LoginWidget::minWindow);
    qInfo() << "connect QToolButton::clicked to LoginWidget::minWindow";

    connect(ui->pushButtonLogin,&QPushButton::clicked,this,&LoginWidget::login);
    qInfo() << "connect QPushButton::clicked to LoginWidget::login";

    // 系统托盘
    connect(systemTray,&zsj::SystemTray::sigDefaultOpen,this,&LoginWidget::show);
    qInfo() << "connect zsj::SystemTray::sigDefaultOpen to LoginWidget::show";
    connect(systemTray,&zsj::SystemTray::sigDefaultQuit,qApp,&QApplication::quit);
    qInfo() << "connect zsj::SystemTray::sigDefaultQuit to QApplication::quit";
    connect(systemTray,&zsj::SystemTray::sigOpenWindow,this,&LoginWidget::show);
    qInfo() << "connect zsj::SystemTray::sigOpenWindow to LoginWidget::show";

    connect(ui->pushButtonLoginCancel,&QPushButton::clicked,this,&LoginWidget::cancelLogin);
    connect(ui->pushButtonCancelLogin,&QPushButton::clicked,this,&LoginWidget::cancelLogin);
    qInfo() << "connect QPushButton::clicked to LoginWidget::cancelLogin";


    connect(ui->toolButtonFindPwd,&QToolButton::clicked,this,&LoginWidget::findPassword);
    connect(ui->pushButtonFindPwd2,&QPushButton::clicked,this,&LoginWidget::findPassword);
    connect(ui->pushButtonFindPwd,&QPushButton::clicked,this,&LoginWidget::findPassword);
    qInfo() << "connect QPushButton::clicked to LoginWidget::findPassword";

}



void LoginWidget::closeWindow()
{
    qApp->quit();
}

void LoginWidget::minWindow()
{
    this->hide();
}

void LoginWidget::setAccountAndPassword(const QPixmap &head, const QString & accountNum, const QString &password)
{
    ui->labelHeadImage->setPixmap(head);
    ui->lineEditOuterInput->setText(accountNum);
    ui->comboBoxAccount->setCurrentText(password);
    ui->lineEditPwd->setText(password);
}

void LoginWidget::showComboBoxPopus()
{
    ui->comboBoxAccount->showPopup();
}

void LoginWidget::login()
{
    QString account = ui->lineEditOuterInput->text();
    QString password = ui->lineEditPwd->text();
    if(account.isEmpty() || account.isNull()){
        QPoint point = ui->lineEditOuterInput->mapToGlobal(ui->lineEditOuterInput->pos()) - QPoint(90,25);
        qDebug() << point;
        toolTip->showToolTip("请你输入账号后再登录",point.x(),point.y());
        return;
    }

    if(password.isEmpty() || password.isNull()){
        QPoint point = ui->lineEditPwd->mapToGlobal(ui->lineEditPwd->pos()) - QPoint(90,67);
        qDebug() << point;
        toolTip->showToolTip("请你输入密码后再登录",point.x(),point.y());
        return;
    }

    ui->stackedWidget->setCurrentIndex(1);

//    QTimer * timer = new QTimer(this);
    QTimer::singleShot(3000,this,[=](){
        if(ui->stackedWidget->currentIndex() != 0){
            ui->stackedWidget->setCurrentIndex(0);
            if(account == "123"){
                qDebug() << "登录成功";
            }
            else{
                ui->stackedWidget->setCurrentIndex(2);
            }
        }
    });
}

void LoginWidget::cancelLogin()
{
    if(ui->stackedWidget->currentIndex() != 0){
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void LoginWidget::findPassword()
{
    zsj::openUrl();
}
