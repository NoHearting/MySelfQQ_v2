#include "Test.h"

#include <QApplication>
#include <QString>
#include <QDebug>
#include <QDesktopWidget>
#include <QWidget>

namespace zsj {

Test::Test()
{

}

void Test::test()
{
    testQApplication();
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

}


