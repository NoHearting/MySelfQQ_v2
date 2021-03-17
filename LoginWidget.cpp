#include "LoginWidget.h"
#include "ui_LoginWidget.h"
#include "utils/Util.h"

#include "main/ReadQStyleSheet.h"
#include "main/Frameless.h"
#include "main/UserData.h"


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
    qInfo() << "deconstruct LoginWidget";
    deleteObjects();
    delete ui;
}

void LoginWidget::initObjects()
{
    // 组合框
    comboBoxListWidget = new QListWidget(this);

    // 初始化系统托盘
    systemTray = new zsj::SystemTray;
    systemTray->showSystemTray();  //显示

    toolTip = new ToolTipWidget;

    frameless = new zsj::Frameless(this);
    frameless->setResizeEnable(false);
}

void LoginWidget::deleteObjects()
{
    if(systemTray){
        systemTray->closeTray();
        delete systemTray;
        systemTray = nullptr;
    }
    if(toolTip){
        delete toolTip;
        toolTip = nullptr;
    }
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
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setAttribute(Qt::WA_QuitOnClose);

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
        connect(item,&ComboBoxItemWidget::click,this,&LoginWidget::slotSetAccountAndPassword);
        qInfo() << "connect ComboBoxItemWidget click to LoginWidget::slotSetAccountAndPassword";
        comboBoxListWidget->setItemWidget(widgetItem,item);
        widgetItem->setSizeHint(QSize(235,50));
    }

    ui->lineEditOuterInput->setText("123");
    ui->lineEditPwd->setText("123");
}

void LoginWidget::initSignalsAndSlots()
{
    connect(ui->toolButtonClose,&QToolButton::clicked,this,&LoginWidget::slotCloseWindow);
    connect(ui->toolButtonCloseLogin,&QToolButton::clicked,this,&LoginWidget::slotCloseWindow);
    connect(ui->toolButtonCloseLoginError,&QToolButton::clicked,this,&LoginWidget::slotCloseWindow);
    qInfo() << "connect toolButtonClose clicked to LoginWidget::slotCloseWindow";

    connect(ui->pushButtonDropDown,&QPushButton::clicked,this,&LoginWidget::slotShowComboBoxPopus);
    qInfo() << "connect QPushButton cliecked to LoginWidget::slotShowComboBoxPopus";

    connect(ui->comboBoxAccount,&MyComboBox::setLineEditCssOn,this,[=](){
        ui->lineEditOuterInput->setStyleSheet("#lineEditOuterInput{border-bottom:1px solid rgb(18,183,245);"
                                           "background:left top no-repeat url('://res/login/logo2.png');}");
        ui->pushButtonDropDown->setStyleSheet("background:url('://res/login/arrow-on.png');");
    });
    qInfo() << "connect MyComboBox::setLineEditCssOn to lambda func to set css";

    /// 设置密码框的样式
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


    connect(ui->toolButtonMin,&QToolButton::clicked,this,&LoginWidget::slotMinWindow);
    connect(ui->toolButtonMinLogin,&QToolButton::clicked,this,&LoginWidget::slotMinWindow);
    connect(ui->toolButtonMinLoginError,&QToolButton::clicked,this,&LoginWidget::slotMinWindow);
    qInfo() << "connect QToolButton::clicked to LoginWidget::slotMinWindow";

    connect(ui->pushButtonLogin,&QPushButton::clicked,this,&LoginWidget::slotLogin);
    qInfo() << "connect QPushButton::clicked to LoginWidget::login";

    // 系统托盘
    connect(systemTray,&zsj::SystemTray::sigDefaultOpen,this,&LoginWidget::show);
    qInfo() << "connect zsj::SystemTray::sigDefaultOpen to LoginWidget::show";
    connect(systemTray,&zsj::SystemTray::sigDefaultQuit,qApp,&QApplication::quit);
    qInfo() << "connect zsj::SystemTray::sigDefaultQuit to QApplication::quit";
    connect(systemTray,&zsj::SystemTray::sigOpenWindow,this,&LoginWidget::show);
    qInfo() << "connect zsj::SystemTray::sigOpenWindow to LoginWidget::show";

    connect(ui->pushButtonLoginCancel,&QPushButton::clicked,this,&LoginWidget::slotCancelLogin);
    connect(ui->pushButtonCancelLogin,&QPushButton::clicked,this,&LoginWidget::slotCancelLogin);
    qInfo() << "connect QPushButton::clicked to LoginWidget::cancelLogin";


    connect(ui->toolButtonFindPwd,&QToolButton::clicked,this,&LoginWidget::slotFindPassword);
    connect(ui->pushButtonFindPwd2,&QPushButton::clicked,this,&LoginWidget::slotFindPassword);
    connect(ui->pushButtonFindPwd,&QPushButton::clicked,this,&LoginWidget::slotFindPassword);
    qInfo() << "connect QPushButton::clicked to LoginWidget::slotFindPassword";

}



void LoginWidget::slotCloseWindow()
{
    close();
}

void LoginWidget::slotMinWindow()
{
    this->hide();
}

void LoginWidget::slotSetAccountAndPassword(const QPixmap &head, const QString & accountNum, const QString &password)
{
    ui->labelHeadImage->setPixmap(head);
    ui->lineEditOuterInput->setText(accountNum);
    ui->comboBoxAccount->setCurrentText(password);
    ui->lineEditPwd->setText(password);
}

void LoginWidget::slotShowComboBoxPopus()
{
    ui->comboBoxAccount->showPopup();
}

void LoginWidget::slotLogin()
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

    QTimer::singleShot(1000,this,[=](){
        if(ui->stackedWidget->currentIndex() != 0){
            ui->stackedWidget->setCurrentIndex(0);
            if(account == "123"){
                qDebug() << "登录成功";
                emit sigLoginSuccess(zsj::Data::ptr(new zsj::UserData));
            }
            else{
                ui->stackedWidget->setCurrentIndex(2);
            }
        }
    });
}

void LoginWidget::slotCancelLogin()
{
    if(ui->stackedWidget->currentIndex() != 0){
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void LoginWidget::slotFindPassword()
{
    zsj::openUrl();
}
