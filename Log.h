#ifndef LOG_H
#define LOG_H

#include <memory>

#include <qlogging.h>
#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>

namespace zsj {

class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    LogAppender(QtMsgType level = QtDebugMsg):level(level){}
    ~LogAppender(){}
    virtual void log(QtMsgType level,const QString & content) = 0;
protected:
    QtMsgType level;            //日志级别
};


class StdoutLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    StdoutLogAppender(QtMsgType level = QtDebugMsg):LogAppender(level){
        stream = new QTextStream(stdout);
    }
    ~StdoutLogAppender(){
        delete stream;
    }

    virtual void log(QtMsgType level, const QString &content)override;
private:
    QTextStream * stream;       //标准输出流
};

class FileLogAppender : public LogAppender{
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(QtMsgType level = QtDebugMsg,const QString & filename = "");
    ~FileLogAppender();
    virtual void log(QtMsgType level, const QString &content)override;

private:
    QFile * file;           //日志文件
    QString path;           //日志文件路径
    QString name;           //日志文件名称
    QString fullName;       //日志文件全名
};


class Logger
{
public:
    typedef std::shared_ptr<Logger> ptr;

    static Logger::ptr Instance();


    void log(QtMsgType level,const QString & content);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    void clearAppenders(){appenders.clear();}
private:
    Logger(QtMsgType level = QtDebugMsg);
    Logger(const Logger &);
    Logger & operator=(const Logger &);

private:
    QtMsgType level;        //日志级别
    QList<LogAppender::ptr> appenders;      //输出器
    static Logger::ptr logger;
};

}



#endif // LOG_H
