#include "Test.h"

#include <QApplication>
#include <QString>
#include <QDebug>
#include <QDesktopWidget>
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QFileInfo>

#include "ReadQStyleSheet.h"

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
}

void Test::testFile()
{
    qDebug() << zsj::ReadQStyleSheet::readQss("://css/main.css");
    qDebug() << "=====================================================";
    qDebug() << zsj::ReadQStyleSheet::readQss("://css/userMenu.css");
}

}


