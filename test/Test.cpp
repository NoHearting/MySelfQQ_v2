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

#include "main/ReadQStyleSheet.h"

namespace zsj {

Test::Test()
{

}

void Test::test()
{
    testQApplication();
//    testFile();
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

}


