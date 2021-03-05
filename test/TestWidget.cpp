#include "TestWidget.h"
#include "ui_TestWidget.h"

#include <QFile>
#include <QFileInfo>
#include <QString>
#include "utils/Util.h"
#include "main/ChatMessageRecord.h"

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidget)
{
    ui->setupUi(this);
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::on_pushButton_clicked()
{
    zsj::ChatMessageRecord chatMessageRecord(QDateTime::currentDateTime(),"111","222",zsj::MessageBodyPtr(new zsj::TextMessageBody("hello world")));
    qDebug() << __LINE__ << "     " <<chatMessageRecord.getMessageBody()->serializeToJson();

    QString tempPath = "/record/temp/";
    QString fileName = "record.txt";

    QString currenPath = zsj::SystemUtil::getProcessPath();
    QString path = currenPath + tempPath;
    bool isOk = zsj::FileUtil::judgeAndMakeDir(path);
    if(isOk){
        qDebug() << __LINE__ <<  " create " << path << " success";
    }
    else{
        qCritical() << "create " << path << " failed!";
        return;
    }
    QString filePath = path + fileName;
    QFile file(filePath);
    if(!file.open(QIODevice::Append | QIODevice::WriteOnly)){
        qCritical() << "open " << filePath << " failed!";
        return;
    }
    file.write(chatMessageRecord.serializeToJson().toStdString().data());
    file.write("\n");
    file.close();
}

void TestWidget::on_pushButton_2_clicked()
{
    QString tempPath = "/record/temp/";
    QString fileName = "record.txt";

    QString currenPath = zsj::SystemUtil::getProcessPath();
    QString path = currenPath + tempPath;
    QString filePath = path + fileName;
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << "open " << filePath << " failed!";
        return;
    }
    while(!file.atEnd()){
        QString line = file.readLine();
        qDebug() << "line >>>> " << line;
        zsj::ChatMessageRecord messgaeRecord = zsj::ChatMessageRecord::DeserializationFromJson(line);
        qDebug() << "json >>>> " << messgaeRecord.serializeToJson();
    }
    file.close();
}
