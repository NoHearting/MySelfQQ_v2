#include "Log.h"
#include "utils/Util.h"

#include <QStringList>
#include <QMutex>
#include <QMutexLocker>
#include <QTextStream>
#include <QDateTime>
#include <QApplication>

namespace zsj
{

Logger::ptr Logger::logger;
Logger* Logger::Instance()
{
    if(!logger)
    {
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if(!logger)
        {
            logger.reset(new Logger(QtDebugMsg));
        }
    }
    return logger.get();
}

void Logger::log(QtMsgType level, const QString &content)
{
    if(level >= this->level)
    {
        if(!appenders.empty())
        {
            for(auto &iter : appenders)
            {
                iter->log(level, content);
            }
        }
        else
        {
            QTextStream(stdout) << __FILE__ << ":" << __LINE__ << "no appender to print log!  \n";
        }
    }
}

void Logger::addAppender(LogAppender::ptr appender)
{
    appenders.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender)
{
    appenders.removeOne(appender);
}

Logger::~Logger()
{
    QTextStream stream(stdout);
    stream << "Logger deconstruct\n";
//    qDebug() << "xxxxx";
}

Logger::Logger(QtMsgType level)
    : level(level)
{
    //初始化两个日志输出器
    appenders.append(std::shared_ptr<StdoutLogAppender>(new StdoutLogAppender(level)));
    appenders.append(std::shared_ptr<FileLogAppender>(new FileLogAppender(level)));
}

Logger::Logger(const Logger &)
{

}

Logger &Logger::operator=(const Logger &)
{
    return *this;
}





zsj::FileLogAppender::FileLogAppender(QtMsgType level, const QString &filename)
    : zsj::LogAppender(level)
{
    if(!filename.isEmpty())
    {
        //默认取应用程序可在执行文件名称
        QString str = qApp->applicationFilePath();
        QStringList list = str.split("/");
        this->name = list.at(list.count() - 1).split(".").at(0);
    }
    else
    {
        this->name = filename;
    }
    path = qApp->applicationDirPath();
    fullName = "";
    file = new QFile();
}

zsj::FileLogAppender::~FileLogAppender()
{
    if(file->isOpen())
    {
        file->close();
    }
}

void zsj::FileLogAppender::log(QtMsgType level, const QString &content)
{
    if(level >= this->level)
    {
        QString fileName = QString("%1/%2_log_%3.log").arg(path).arg(name).arg(GetCurrentDateTime());
        if(fullName != fileName)
        {
            fullName = fileName;
            if(file->isOpen())
            {
                file->close();
            }
            file->setFileName(fileName);
            file->open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
        }

        QTextStream logStream(file);
        logStream  << content << "\n";
    }
}

void zsj::StdoutLogAppender::log(QtMsgType level, const QString &content)
{
    if(level >= this->level)
    {
        *stream << content << "\n";
        stream->flush();
    }
}

}
