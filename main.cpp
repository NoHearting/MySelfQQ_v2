#include "LoginWidget.h"
#include "Util.h"
#include "Log.h"
#include "Test.h"

#include <QApplication>
#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>
#include <QThread>
#include <QDebug>

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg);
void printAppInfo();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //安装日志处理钩子函数
    qInstallMessageHandler(outputMessage);

    printAppInfo();

    LoginWidget w;
    w.show();

    Zsj::Test().test();
    return a.exec();


}

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QMutex mutex;
    QMutexLocker loccker(&mutex);
    QString category;
    switch(type){
    case QtDebugMsg:
        category.sprintf("[%10s]",qPrintable("Debug"));
        break;
    case QtInfoMsg:
        category.sprintf("[%10s]",qPrintable("Info"));
        break;
    case QtWarningMsg:
        category.sprintf("[%10s]",qPrintable("Warn"));
        break;
    case QtCriticalMsg:
        category.sprintf("[%10s]",qPrintable("Critical"));
        break;
    case QtFatalMsg:
        category.sprintf("[%10s]",qPrintable("Fatal"));
        break;
    }
    QString tab = "\t";
    int threadId = (int)QThread::currentThreadId();
    int pid = Zsj::getCurrentProcessId();
    QString date = Zsj::GetCurrentDateTime("yyyy-MM-dd hh:mm:ss");

    //format : category pid tid file line date message
    QString content = QString("%2 [%3:%4] [%6:%7] %8%1%9")
            .arg(tab)
            .arg(category)
            .arg(pid)
            .arg(threadId)
            .arg(context.file)
            .arg(context.line)
            .arg(date)
            .arg(msg);

    Zsj::Logger::Instance()->log(type,content);
}

void printAppInfo()
{
    qInfo() << "< appName:       " << qApp->applicationName() << ">";
    qInfo() << "< process id:    " << qApp->applicationPid() << ">";
    qInfo() << "< process path:  " << qApp->applicationFilePath() << ">";
}
