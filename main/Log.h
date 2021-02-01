/**
  * @brief 日志封装，配合Qt的日志系统
  *
  * @author zsj
  * @date 2020年12月23日20:07:44
  */
#ifndef LOG_H
#define LOG_H

#include <memory>

#include <qlogging.h>
#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>

namespace zsj {

/// @brief 日志输出器，通过此类将日志输出到指定位置
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    LogAppender(QtMsgType level = QtDebugMsg):level(level){}
    virtual ~LogAppender(){}
    virtual void log(QtMsgType level,const QString & content) = 0;
protected:
    QtMsgType level;            //日志级别
};

/// @brief 标准输出流输出器，用于将日志输出到控制台
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

/// @brief 文件流输出器，用于将体制输出到指定文件
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


/// @brief 日志输出类，可以添加输出器，设置默认日志级别
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
