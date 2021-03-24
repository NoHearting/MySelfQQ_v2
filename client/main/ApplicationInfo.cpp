#include "ApplicationInfo.h"


#include <QMutex>
#include <QMutexLocker>

namespace zsj {

ApplicationInfo::App ApplicationInfo::app;

ApplicationInfo::ApplicationInfo()
{

}

QString ApplicationInfo::getAppAbsoluteDir() const
{
    return appAbsoluteDir;
}

void ApplicationInfo::setAppAbsoluteDir(const QString &value)
{
    appAbsoluteDir = value;
}


QString ApplicationInfo::getAppVersion() const
{
    return appVersion;
}

void ApplicationInfo::setAppVersion(const QString &value)
{
    appVersion = value;
}

ApplicationInfo *ApplicationInfo::Instance()
{
    if(app.isNull()){
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if(app.isNull()){
            app.reset(new ApplicationInfo);
        }
    }
    return app.get();
}


quint64 ApplicationInfo::getAppPid() const
{
    return appPid;
}

void ApplicationInfo::setAppPid(const quint64 &value)
{
    appPid = value;
}


QString ApplicationInfo::getAppAbsolutePath() const
{
    return appAbsolutePath;
}

void ApplicationInfo::setAppAbsolutePath(const QString &value)
{
    appAbsolutePath = value;
}



QString ApplicationInfo::getAppName() const
{
    return appName;
}

void ApplicationInfo::setAppName(const QString &value)
{
    appName = value;
}

}
