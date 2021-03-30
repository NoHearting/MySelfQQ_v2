#include "LoginWidget.h"
#include "utils/Util.h"
#include "main/Log.h"
#include "test/Test.h"
#include "MainWidget.h"
#include "ChatWidget.h"
#include "utils/Global.h"
#include "test/TestWidget.h"

#include <QApplication>
#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>
#include <QThread>
#include <QDebug>
#include <QScopedPointer>

#include <QtGlobal>
#include <QTime>
#include <QObject>

#include "main/UserData.h"
#include "main/ApplicationInfo.h"

QScopedPointer<MainWidget> mainWidget;
QScopedPointer<LoginWidget> loginWidget;

#define TEST 0

/**
 * @brief 打印日志的钩子函数
 * @param type  消息类型
 * @param context
 * @param msg
 */
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);

/**
 * @brief 打印app信息
 */
void printAppInfo();

/**
 * @brief 登录的回调函数
 * @param loginWidget 登录界面
 * @param userData 登录成功后的用户数据
 */
void slotLoginSuccess(zsj::Data::ptr userData);

int main(int argc, char *argv[])
{
#if TEST
    QApplication a(argc, argv);

    //安装日志处理钩子函数
    qInstallMessageHandler(outputMessage);

    printAppInfo();
//    TestWidget testWidget;
//    testWidget.show();
    zsj::Test().test();
    return a.exec();
#else
    QApplication a(argc, argv);

#ifdef DEBUG
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    // msg
#endif

    //安装日志处理钩子函数
    qInstallMessageHandler(outputMessage);

    printAppInfo();

    loginWidget.reset(new LoginWidget);
    loginWidget->show();
    QObject::connect(loginWidget.get(),&LoginWidget::sigLoginSuccess,&slotLoginSuccess);

//    MainWidget mainWidget(zsj::Data::ptr(new zsj::UserData));
//    mainWidget.show();
//    ChatWidget chatWidget;
//    chatWidget.show();

//    zsj::Test().test();
    return a.exec();
#endif
}

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutex mutex;
    QMutexLocker loccker(&mutex);
    QString category;
    switch(type)
    {
        case QtDebugMsg:
            category.sprintf("[%10s]", qPrintable("Debug"));
            break;
        case QtInfoMsg:
            category.sprintf("[%10s]", qPrintable("Info"));
            break;
        case QtWarningMsg:
            category.sprintf("[%10s]", qPrintable("Warn"));
            break;
        case QtCriticalMsg:
            category.sprintf("[%10s]", qPrintable("Critical"));
            break;
        case QtFatalMsg:
            category.sprintf("[%10s]", qPrintable("Fatal"));
            break;
    }
    QString tab = "\t";
    QString threadId = zsj::SystemUtil::getCurrentThreadId();
    int pid = zsj::SystemUtil::getCurrentProcessId();
    QString date = zsj::GetCurrentDateTime("yyyy-MM-dd hh:mm:ss");

    //format : category pid tid file line date message
    QString content = QString("%2 [%3:%4] [%5:%6] %7%1%8")
                      .arg(tab)
                      .arg(category)
                      .arg(pid)
                      .arg(threadId)
                      .arg(context.file)
                      .arg(context.line)
                      .arg(date)
                      .arg(msg);

    zsj::Logger::Instance()->log(type, content);
}

void printAppInfo()
{
    qInfo() << "< qt version:    " << QT_VERSION_STR;
    qInfo() << "< appName:       " << qApp->applicationName() << ">";
    qInfo() << "< process id:    " << qApp->applicationPid() << ">";
    qInfo() << "< process path:  " << qApp->applicationFilePath() << ">";
    auto app = zsj::ApplicationInfo::Instance();
    app->setAppName(qApp->applicationName());
    app->setAppAbsoluteDir(qApp->applicationDirPath());
    app->setAppAbsolutePath(qApp->applicationFilePath());
    app->setAppPid(qApp->applicationPid());
    app->setAppVersion(qApp->applicationVersion());
}

void slotLoginSuccess(zsj::Data::ptr userData){
//    qDebug() << userData->toString();
    if(loginWidget->isVisible()){
        loginWidget->close();
        loginWidget.reset();
    }
    mainWidget.reset(new MainWidget(userData));
    mainWidget->show();
//    MainWidget * main = new MainWidget(userData);
//    main->show();

}
