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

#include <QRegExp>

#include <QFile>

#include "main/ReadQStyleSheet.h"
#include "utils/Util.h"

namespace zsj
{

Test::Test()
{

}

void Test::test()
{
//    testQApplication();
//    testFile();
//    testDir();
//    testDebugColor();
//    findSubString();
//    testStringReplace();
//    testRemoveStyle();
//    testReg();
    testFontWidth();
}

void Test::testQApplication()
{
    QString appName = qApp->applicationName();
    quint64 pid = qApp->applicationPid();
    QWidget *screen = qApp->desktop()->screen();
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
    if(isOk)
    {
        qDebug() << "mkdir ok";
    }
    else
    {
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

void Test::testDebugColor()
{
    qDebug() << "\033[36m" << "hello";
}

void Test::findSubString()
{
    QString originString = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">hkl看看剧来看<img src=\":/symbol/res/emoji/symbol/b_m.png\" width=\"28\" height=\"28\" />奥术大师大所多<img src=\"D:/QT/QtCode/MySelfQQ_v2/build/build-MySelfQQ_v2-Desktop_Qt_5_12_0_MinGW_64_bit-Debug/debug/screen_shot/2021-03-01-11-40-51.jpg\" width=\"150\" height=\"90\" /></p></body></html>";
    int begin = originString.indexOf("<body");
    int end = originString.indexOf("</body>");
    const int lastCount = QString("</p></body></html>").size();
    qDebug() << begin << " - " << end << " - " << originString.size();
    qDebug() << originString.mid(begin);
}

void Test::testStringReplace()
{
    QString str = "<img src=':/normal/res/emoji/normal/biz.png' width=28 height=28></img>";
    QString temp = str.replace("28", "16");
    qDebug() << "temp : " << temp;
    qDebug() << "str:   " << str;
}

void Test::testRemoveStyle()
{

    qDebug() << (0x001F00 & 0x000100);
    QString path = "Z:\\default\\Desktop\\temp.html";
    path = path.toLocal8Bit();
    qDebug() << path.toStdString().data();
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "file open failed!";
        return;
    }
    QString originStr = QString(file.readAll().toStdString().data());
    QString result = zsj::HtmlUtil::RemoveOriginTagStyle(originStr, static_cast<zsj::TagType>(
                         zsj::TAG_ALL));
    qDebug() << result;
}

void Test::testReg()
{
    QString origin = "<body><h3><span>重要事务</span></h3>";
    QRegExp rx("(</?\\w{0,10}>)");
    QStringList list;
    int pos = 0;

    while ((pos = rx.indexIn(origin, pos)) != -1) {
        list << rx.cap(1);
        pos += rx.matchedLength();
    }
    qDebug() << list;
}

void Test::testFontWidth()
{
    QFont font = QFont("微软雅黑",18);
    QFont newFont(font.family(), font.pixelSize());
    QFontMetrics fm(newFont);
    QString testStr = "[测试字符]";
    int height = fm.height();
    int pixSize = font.pixelSize();
    int pointSize = font.pointSize();
    qDebug() << "pixSize: " << pixSize << " "
             << "pointSize:" << pointSize;  // -1 18
    int width = fm.width("[");
    qDebug() << "height: " << height << "  "
             << "width:  " << width; // 21 5
    int sizeWidth = height * testStr.size();
    int pixWidth = fm.horizontalAdvance(testStr);
    qDebug() << "sizeWidth: " << sizeWidth << "  "
             << "pixWidth: " << pixWidth; //126  74
}


}


