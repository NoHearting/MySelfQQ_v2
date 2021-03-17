#include "Test.h"

#include <QApplication>
#include <QString>
#include <QDebug>
#include <QDesktopWidget>
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>

#include <QtGlobal>
#include <QMap>
#include <queue>
#include <QPair>
#include <QVector>
#include <utility>
#include <vector>
#include <iostream>

#include <QRegExp>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSharedPointer>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QFile>

#include "main/ReadQStyleSheet.h"
#include "utils/Util.h"
#include "dao/LoginInfoDao.h"
#include "main/LoginInfo.h"
#include "main/ApplicationInfo.h"

#include <utils/Util.h>

#include <memory>

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
//    testFontWidth();
//    testJson();
//    testChatMessageRecord();
//    testQSharedPointer();

//    testCode();
    testSqlite();
}

void Test::testQApplication()
{
    qDebug() << "applicationName : " << qApp->applicationName();
    qDebug() << "applicationPid : " << qApp->applicationPid();
    qDebug() << "applicationDirPath : " << qApp->applicationDirPath();
    qDebug() << "applicationDisplayName : " << qApp->applicationDisplayName();
    qDebug() << "applicationFilePath : " << qApp->applicationFilePath();
    qDebug() << "applicationState : " << qApp->applicationState();
    qDebug() << "applicationVersion : " << qApp->applicationVersion();

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

    while ((pos = rx.indexIn(origin, pos)) != -1)
    {
        list << rx.cap(1);
        pos += rx.matchedLength();
    }
    qDebug() << list;
}

void Test::testFontWidth()
{
    QFont font = QFont("微软雅黑", 18);
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

void Test::testJson()
{
    QString jsonStr = "{\"name\":\"zsj\",\"age\":12}";
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toLatin1());
    if(!doc.isNull() && !doc.isEmpty())
    {
        QJsonObject obj = doc.object();
        qDebug() << "name: " << obj.value("name").toString()
                 << "age : " << obj.value("age").toInt();
        qDebug() << doc.toJson().data();
    }
    else
    {
        qCritical() << "doc is null";
    }
}

void Test::testChatMessageRecord()
{
    zsj::ChatMessageRecord chatMessageRecord(QDateTime::currentDateTime(), "111", "222", MessageBodyPtr(new TextMessageBody("hello world")));
    qDebug() << chatMessageRecord.serializeToJson();

    QString tempPath = "/record/temp/";
    QString fileName = "record.txt";

    QString currenPath = SystemUtil::getProcessPath();
    QString path = currenPath + tempPath;
    bool isOk = FileUtil::judgeAndMakeDir(path);
    if(isOk)
    {
        qDebug() << __LINE__ <<  " create " << path << " success";
    }
    else
    {
        qCritical() << "create " << path << " failed!";
        return;
    }
    QString filePath = path + fileName;
    QFile file(filePath);
    if(!file.open(QIODevice::Append | QIODevice::WriteOnly))
    {
        qCritical() << "open " << filePath << " failed!";
        return;
    }
//    QTextStream out(&file);
    file.write(chatMessageRecord.serializeToJson().toStdString().data());
    file.write("\n");
    file.close();
}

class Base
{
public:
    virtual ~Base() {}
    virtual void show()
    {
        qDebug() << "base";
    }
};

class Derive : public Base
{
public:
    void show()override
    {
        qDebug() << "Derive";
    }
};

void Test::testQSharedPointer()
{
//    std::shared_ptr<>();
//    QSharedPointer()

    std::shared_ptr<Base> base(new Base);
    qDebug() << "base";
    std::shared_ptr<Derive> derive = std::dynamic_pointer_cast<Derive>(base);
    qDebug() << "cast and assign success";
    if(!derive)
    {
        derive->show();
    }


    //    std::dynamic_pointer_cast
}

void Test::testCode()
{
    //    Qt::Key_A
}

void Test::testSqlite()
{
//    QSqlDatabase database;
//    database = QSqlDatabase::addDatabase("QSQLITE");
//    database.setDatabaseName("./data/test.db");
//    if (!database.open())
//    {
//        qDebug() << "Error: Failed to connect database." << database.lastError();
//        return;
//    }
//    else
//    {
//        qDebug() << "Succeed to connect database." ;
//    }
//    QSqlQuery query(database);
//    query.prepare("select * from login_info");
////    bool ret = query.exec("select * from login_info");
//    bool ret = query.exec();
//    if(ret){
//        while(query.next()){
//            qDebug() << query.value(0).toInt();
//            qDebug() << query.value(1).toString();
//        }
//    }
//    else{
//        qCritical() << query.lastError();
//    }

    testDao();
}

void Test::testDao()
{
//    zsj::LoginInfoDao dao;
//    QVector<zsj::LoginInfo> infos = dao.listLoginInfo();
//    for(const auto &item : infos)
//    {
//        qDebug() << item.toString();
//    }
//    qDebug() << infos.size();
    zsj::LoginInfoDao dao;
    LoginInfo info(0,"head","昵称",1235123,"zsj",false,false);
    bool ret = dao.insertLoginInfo(info);
    if(!ret){
        qDebug() << "insert Data failed!";
    }
    else{
        qDebug() << "isnert data success!";
    }
}


}


