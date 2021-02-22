#include "Test.h"

#include <QApplication>
#include <QString>
#include <QDebug>
#include <QDesktopWidget>
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QFileInfo>

#include <QtGlobal>
#include <QMap>
#include <queue>
#include <QPair>

#include "main/ReadQStyleSheet.h"
#include "utils/Util.h"

namespace zsj {

Test::Test()
{

}

void Test::test()
{
//    testQApplication();
//    testFile();
    testDir();
}

void Test::testQApplication()
{
    QString appName = qApp->applicationName();
    quint64 pid= qApp->applicationPid();
    QWidget * screen = qApp->desktop()->screen();
    qDebug() << appName;
    qDebug() << pid;
    qDebug() << screen->width() << ":" << screen->height();
    qDebug() << "availableGeometry: " << qApp->desktop()->availableGeometry();
}

void Test::testFile()
{
    qDebug() << zsj::ReadQStyleSheet::readQss("://css/main.css");
    qDebug() << "=====================================================";
    qDebug() << zsj::ReadQStyleSheet::readQss("://css/userMenu.css");
}

void Test::testDir()
{
    bool isOk = zsj::FileUtil::judgeAndMakeDir("D:/TestDir/test1");
    if(isOk){
        qDebug() << "mkdir ok";
    }
    else{
        qDebug() << "mkdir failed";
    }
}

void Test::testGlobalMacroSystem()
{
#ifdef Q_OS_WIN64
    qDebug() << "windows32";
#elif defined(Q_OS_WIN32)
    qDebug() << "windows64";
#elif defined(Q_OS_LINUX)
    qDebug() << "linux";
#elif defined(Q_OS_MAC)
    qDebug() << "mac";
#elif defined(Q_OS_IOS)
    qDebug() << "ios";
#elif defined(Q_OS_UNIX)
    qDebug() << "unix";
#elif defined(Q_PROCESSOR_ARM)
    qDebug() << "arm";
#elif defined(Q_OS_ANDROID)
    qDebug() << "android";
#endif

#ifdef Q_OS_LINUX
    qDebug() << "linux";
#endif
}

void Test::testQueue()
{
//    std::priority_queue<QPair<
}


}


