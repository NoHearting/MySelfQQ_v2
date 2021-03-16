#include "TestWidget.h"
#include "ui_TestWidget.h"

#include <QFile>
#include <QFileInfo>
#include <QString>
#include <memory>
#include "utils/Util.h"
#include "main/ChatMessageRecord.h"

#include <QDebug>
#include <QCloseEvent>

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidget)
{
    ui->setupUi(this);
    string = new QString("");
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::closeEvent(QCloseEvent *event)
{
    qDebug() << "closeEvent";
    event->ignore();
    qApp->quit();
}

void outToFile()
{
    zsj::ChatMessageRecord chatMessageRecord(QDateTime::currentDateTime(), "111", "222", zsj::MessageBodyPtr(new zsj::TextMessageBody("hello world")));
    qDebug() << __LINE__ << "     " << chatMessageRecord.getMessageBody()->serializeToJson();

    QString tempPath = "/record/temp/";
    QString fileName = "record.txt";

    QString currenPath = zsj::SystemUtil::getProcessPath();
    QString path = currenPath + tempPath;
    bool isOk = zsj::FileUtil::judgeAndMakeDir(path);
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
    file.write(chatMessageRecord.serializeToJson().toStdString().data());
    file.write("\n");
    file.close();
}

class Base{
public:
    virtual ~Base(){qDebug() << "deconstruct Base";}
    virtual void show(){qDebug() << "base func";}

};

class Derive : public Base{
public:
    void show()override{qDebug() <<"Derive func";}
    ~Derive(){qDebug() << "deconstruct Derive";}
};

void testSharedPointerCast(){
    std::shared_ptr<Base> base(new Derive);
    qDebug() << "base";
    std::shared_ptr<Derive> derive = std::dynamic_pointer_cast<Derive>(base);
    qDebug() << "cast and assign success";
    if(derive)
    {
            derive->show();
    }

//    std::dynamic_pointer_cast

}

void TestWidget::on_pushButton_clicked()
{
    testSharedPointerCast();
}

void TestWidget::on_pushButton_2_clicked()
{
    QString tempPath = "/record/temp/";
    QString fileName = "record.txt";

    QString currenPath = zsj::SystemUtil::getProcessPath();
    QString path = currenPath + tempPath;
    QString filePath = path + fileName;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "open " << filePath << " failed!";
        return;
    }
    while(!file.atEnd())
    {
        QString line = file.readLine();
        qDebug() << "line >>>> " << line;
        zsj::ChatMessageRecord messgaeRecord = zsj::ChatMessageRecord::DeserializationFromJson(line);
        qDebug() << "json >>>> " << messgaeRecord.serializeToJson();
    }
    file.close();
}
