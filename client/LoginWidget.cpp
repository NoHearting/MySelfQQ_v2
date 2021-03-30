#include "LoginWidget.h"
#include "ui_LoginWidget.h"
#include "utils/Util.h"

#include "main/ReadQStyleSheet.h"
#include "main/Frameless.h"
#include "main/UserData.h"
#include "main/LoginInfo.h"
#include "main/ApplicationInfo.h"


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
#include <QDateTime>


LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    initObjects();
    initResourceAndForm();
    initSignalsAndSlots();

    loadAndSetLoginInfo();
}

LoginWidget::~LoginWidget()
{
//    qInfo() << "deconstruct LoginWidget";
    QTextStream stream(stdout);
    stream << "deconstruct LoginWidget\n";
    deleteObjects();
    delete ui;
}

void LoginWidget::initObjects()
{
    // 组合框
    comboBoxListWidget = new QListWidget();

    infoDao = new zsj::LoginInfoDao;

    // 初始化系统托盘
    systemTray = new zsj::SystemTray;
    systemTray->showSystemTray();  //显示

    toolTip = new ToolTipWidget;

    frameless = new zsj::Frameless(this);
    frameless->setResizeEnable(false);

    popupWidget = new PopupWidget(ui->lineEditOuterInput);

    loginService = new zsj::LoginWebService;
}

void LoginWidget::deleteObjects()
{

    systemTray->closeTray();
    delete systemTray;
    systemTray = nullptr;


    delete toolTip;
    toolTip = nullptr;

    delete infoDao;
    infoDao = nullptr;

    delete popupWidget;
    popupWidget = nullptr;

    delete loginService;
    loginService = nullptr;
}

void LoginWidget::loadAndSetLoginInfo()
{
    infos = infoDao->listLoginInfo();
    qDebug() << infos.size();
    if(!infos.empty())
    {
        // 读取记录第一条并且设置
        zsj::LoginInfo info = infos[0];
        ui->lineEditOuterInput->setText(QString::number(info.getAccount()));
        ui->checkBoxAutoLogin->setChecked(info.getSavePassword());
        if(info.getSavePassword())
        {
            ui->checkBoxRememberPwd->setChecked(true);
            ui->lineEditPwd->setText(info.getPassword());
        }
        QString headPath = info.getHead();
        QPixmap pix(headPath);

        QPixmap head = zsj::adjustToHead(pix,zsj::HeadSize::loginMainDiameter);
//        QPixmap head = zsj::scaledPixmap(pix,zsj::HeadSize::loginMainDiameter,zsj::HeadSize::loginMainDiameter);
        ui->labelHeadImage->setPixmap(head);
        ui->labelHeadImageLogin->setPixmap(head);

        // 设置后续的item
        for(int i = 0; i < infos.size(); i++)
        {
            popupWidget->addItem(infos.at(i));
        }
    }
    else
    {
        qInfo() << "login info is empty.";
    }
}

void LoginWidget::persistenceLoginInfo(zsj::LoginInfo &info)
{
    for(auto &item : infos)
    {
        if(info.getAccount() == item.getAccount())
        {
            info.setLastUpdate(QDateTime::currentDateTime().toTime_t());
            bool ret = infoDao->updateLoginInfo(info);
            if(!ret)
            {
                qCritical() << "persistence login info failed!";
            }
            return;
        }
    }
    bool ret = infoDao->insertLoginInfo(info);
    if(!ret)
    {
        qCritical() << "persistence login info failed!";
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
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);  //阴影偏移量
    shadow->setColor(Qt::black);  //阴影颜色
    shadow->setBlurRadius(12);     //阴影的模糊半径
    ui->widgetLogin->setGraphicsEffect(shadow);
    qDebug() << "初始化样式成功";


    QMovie *movie = new QMovie("://res/login/bg-movie.gif");
    ui->labelBgMovie->setMovie(movie);
    ui->labelBgMovieLogin->setMovie(movie);
    movie->start();
    movie->setParent(this);

    // 设置默认头像
    QPixmap pixmap("://res/login/default-head.png");
    head = zsj::pixmapToRound(pixmap, 32);
    ui->labelHeadImage->setPixmap(head);
    ui->labelHeadImageLogin->setPixmap(head);


    comboBoxListWidget->setFixedHeight(180);
    comboBoxListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

void LoginWidget::initSignalsAndSlots()
{
    /// 关闭窗口
    connect(ui->toolButtonClose, &QToolButton::clicked, this, &LoginWidget::slotCloseWindow);
    connect(ui->toolButtonCloseLogin, &QToolButton::clicked, this, &LoginWidget::slotCloseWindow);
    connect(ui->toolButtonCloseLoginError, &QToolButton::clicked, this, &LoginWidget::slotCloseWindow);
    qInfo() << "connect toolButtonClose clicked to LoginWidget::slotCloseWindow";

    /// 展示账号下拉框
    connect(ui->pushButtonDropDown, &QPushButton::clicked, this, &LoginWidget::slotShowComboBoxPopus);
    connect(popupWidget, &PopupWidget::sigHide, this, [ = ]()
    {
        ui->pushButtonDropDown->setChecked(false);
    });
    qInfo() << "connect QPushButton cliecked to LoginWidget::slotShowComboBoxPopus";
    connect(popupWidget, &PopupWidget::sigClick, this, &LoginWidget::slotSetAccountAndPassword);

    /// 最小化窗口
    connect(ui->toolButtonMin, &QToolButton::clicked, this, &LoginWidget::slotMinWindow);
    connect(ui->toolButtonMinLogin, &QToolButton::clicked, this, &LoginWidget::slotMinWindow);
    connect(ui->toolButtonMinLoginError, &QToolButton::clicked, this, &LoginWidget::slotMinWindow);
    qInfo() << "connect QToolButton::clicked to LoginWidget::slotMinWindow";

    /// 点击登录
    connect(ui->pushButtonLogin, &QPushButton::clicked, this, &LoginWidget::slotLogin);
    qInfo() << "connect QPushButton::clicked to LoginWidget::login";

    /// 系统托盘
    connect(systemTray, &zsj::SystemTray::sigDefaultOpen, this, &LoginWidget::show);
    qInfo() << "connect zsj::SystemTray::sigDefaultOpen to LoginWidget::show";
    connect(systemTray, &zsj::SystemTray::sigDefaultQuit, qApp, &QApplication::quit);
    qInfo() << "connect zsj::SystemTray::sigDefaultQuit to QApplication::quit";
    connect(systemTray, &zsj::SystemTray::sigOpenWindow, this, &LoginWidget::show);
    qInfo() << "connect zsj::SystemTray::sigOpenWindow to LoginWidget::show";

    /// 取消登录
    connect(ui->pushButtonLoginCancel, &QPushButton::clicked, this, &LoginWidget::slotCancelLogin);
    connect(ui->pushButtonCancelLogin, &QPushButton::clicked, this, &LoginWidget::slotCancelLogin);
    qInfo() << "connect QPushButton::clicked to LoginWidget::cancelLogin";


    /// 找回密码
    connect(ui->toolButtonFindPwd, &QToolButton::clicked, this, &LoginWidget::slotFindPassword);
    connect(ui->pushButtonFindPwd2, &QPushButton::clicked, this, &LoginWidget::slotFindPassword);
    connect(ui->pushButtonFindPwd, &QPushButton::clicked, this, &LoginWidget::slotFindPassword);
    qInfo() << "connect QPushButton::clicked to LoginWidget::slotFindPassword";

    connect(ui->pushButtonRegister,&QPushButton::clicked,this,[this](){
        zsj::openUrl(zsj::global::BgUrl::Register());
    });


}



void LoginWidget::slotCloseWindow()
{
    close();
}

void LoginWidget::slotMinWindow()
{
    this->hide();
}

void LoginWidget::slotSetAccountAndPassword(zsj::LoginInfo::ptr info)
{
    QPixmap pix(info->getHead());
    QPixmap head = zsj::adjustToHead(pix, zsj::HeadSize::loginMainDiameter);
    ui->labelHeadImage->setPixmap(head);
    ui->lineEditOuterInput->setText(QString::number(info->getAccount()));
//    ui->comboBoxAccount->setCurrentText(QString::number(info->getAccount()));
    ui->lineEditPwd->setText(info->getPassword());
    ui->checkBoxAutoLogin->setChecked(info->getAutoLogin());
    ui->checkBoxRememberPwd->setChecked(info->getSavePassword());

    popupWidget->hide();
}

void LoginWidget::slotShowComboBoxPopus()
{
    if(popupWidget->isVisible()){
        popupWidget->hide();
    }
    else{
        popupWidget->showWindow();
    }
}

void LoginWidget::slotLogin()
{
    QString account = ui->lineEditOuterInput->text();
    QString password = ui->lineEditPwd->text();
    if(account.isEmpty() || account.isNull())
    {
        QPoint point = ui->lineEditOuterInput->mapToGlobal(ui->lineEditOuterInput->pos()) - QPoint(90, 25);
        qDebug() << point;
        toolTip->showToolTip("请你输入账号后再登录", point.x(), point.y());
        return;
    }

    if(password.isEmpty() || password.isNull())
    {
        QPoint point = ui->lineEditPwd->mapToGlobal(ui->lineEditPwd->pos()) - QPoint(90, 67);
        qDebug() << point;
        toolTip->showToolTip("请你输入密码后再登录", point.x(), point.y());
        return;
    }

    ui->stackedWidget->setCurrentIndex(1);



    QJsonObject result = loginService->login(account.toInt(),password);
    if(cancelLogin){
        cancelLogin = false;
        return;
    }
    if(!result.isEmpty()){
        // 登录成功
        if(result.value("status").toBool() == true){
            QJsonObject data = result.value("data").toObject();
            QJsonObject user = data.value("user").toObject();

            QString actPath = zsj::ApplicationInfo::Instance()->getAppAbsoluteDir();
            QString headDir = QString("/image/%1/headImage/").arg(user.value("id").toInt());
            QString headPath = loginService->downloadHeadPicture(
                        user.value("head").toString(),
                        actPath + headDir);
            QPixmap head(headPath);
            QString  nickname = user.value("nickname").toString();
            int id = user.value("id").toInt();
            QString signature = user.value("signature").toString();
            int level = user.value("level").toInt();
            bool vip = user.value("vip").toBool();
            QString pwd = user.value("password").toString();
            zsj::Data::ptr userData(new zsj::UserData(head,nickname,id,signature,"",level,vip));

            zsj::LoginInfo info(0,headPath,nickname,id,pwd,
                                ui->checkBoxAutoLogin->isChecked(),
                                ui->checkBoxRememberPwd->isChecked(),
                                QDateTime::currentDateTime().toTime_t());
            persistenceLoginInfo(info);
            emit sigLoginSuccess(userData);
        }
        else{ // 登录失败
            ui->stackedWidget->setCurrentIndex(2);
        }
    }
    else{
        // 这里应该是程序问题  不是登录错误
        ui->stackedWidget->setCurrentIndex(2);
        qCritical() << "出现未知错误!";
    }
}

void LoginWidget::slotCancelLogin()
{
    if(ui->stackedWidget->currentIndex() != 0)
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    cancelLogin = true;
}

void LoginWidget::slotFindPassword()
{
    zsj::openUrl(zsj::global::BgUrl::FindPassword());
}

