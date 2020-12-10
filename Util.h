#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QDateTime>

namespace Zsj {

#define DEBUG

#ifdef DEBUG
const QString appName = "qtcreator";
#else
const QString appName = "MySelfQQ_v2";
#endif


class Util
{
public:
    Util();
};

int getCurrentProcessId(const QString & processName = appName);


inline QString GetCurrentDateTime(const QString & format = "yyyy-MM-dd"){
    return qPrintable(QDateTime::currentDateTime().toString(format));
}


}
#endif // UTIL_H
