#include <QScopedPointer>
#include <QString>

#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H

namespace zsj {



class ApplicationInfo
{
public:
    typedef QScopedPointer<ApplicationInfo> App;
public:
    static ApplicationInfo * Instance();



    QString getAppName() const;
    void setAppName(const QString &value);

    QString getAppAbsolutePath() const;
    void setAppAbsolutePath(const QString &value);

    quint64 getAppPid() const;
    void setAppPid(const quint64 &value);
    QString getAppVersion() const;
    void setAppVersion(const QString &value);


    QString getAppAbsoluteDir() const;
    void setAppAbsoluteDir(const QString &value);

private:
    ApplicationInfo();

private:
    static App app;

    QString appName;            // 程序名称
    QString appAbsoluteDir;     // 可执行程序所在目录
    QString appAbsolutePath;    // 可执行程序绝对路径
    quint64 appPid;             // 进程号
    QString appVersion;         // 程序版本
};


}
#endif // APPLICATIONINFO_H
