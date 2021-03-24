/**
  * @file CurrentWindow.h
  * @brief 记录当前窗口的信息。
  * @author zsj
  * @date 2021年3月2日09:43:58
  * @note 目前记录当前窗口的geometry。
  */
#ifndef CURRENTWINDOW_H
#define CURRENTWINDOW_H

#include <QSize>
#include <QScopedPointer>
#include <QRect>

namespace zsj {


class CurrentWindow
{
public:
    static CurrentWindow * Instance();
public:

    QRect getWindowGeometry() const;
    void setWindowGeometry(const QRect &value);

private:
    CurrentWindow();
private:
    static QScopedPointer<CurrentWindow> currentWindow;

    QRect windowGeometry;
};

}
#endif // CURRENTWINDOW_H
