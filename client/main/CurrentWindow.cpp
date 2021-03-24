#include "CurrentWindow.h"

#include <QMutex>
#include <QMutexLocker>

namespace zsj {


QScopedPointer<CurrentWindow> CurrentWindow::currentWindow;

CurrentWindow::CurrentWindow()
{

}

CurrentWindow *CurrentWindow::Instance()
{
    if(currentWindow.isNull()){
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        if(currentWindow.isNull()){
            currentWindow.reset(new CurrentWindow);
        }
    }
    return currentWindow.data();
}

QRect CurrentWindow::getWindowGeometry() const
{
    return windowGeometry;
}

void CurrentWindow::setWindowGeometry(const QRect &value)
{
    windowGeometry = value;
}

}
