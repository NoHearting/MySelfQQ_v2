#include "CommonHelper.h"

#include <QFile>
#include <QTranslator>
#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QDebug>

#include <windows.h>

namespace zsj {




const uint WINDOW_BASESIZE_WIDTH = 1920;
const uint WINDOW_BASESIZE_HEIGHT = 1080;

float CommonHelper::widthMultiplyingPower = 0;
float CommonHelper::heightMultiplyingPower = 0;

CommonHelper::CommonHelper()
{

}

void CommonHelper::setStyle(const QString &style)
{
    QFile qss(style);
    bool isOpen = qss.open(QFile::ReadOnly);
    if(isOpen){
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
    else{
        qCritical() << style << "open failed";
    }
}

void CommonHelper::setLanguagePack(const QString &language)
{
    // 加载中文包
    QTranslator translator;
    translator.load(language);
    qApp->installTranslator(&translator);
}

void CommonHelper::moveCenter(QWidget *widget, QRect parentRect)
{
    if(parentRect.isEmpty()){
        parentRect = QApplication::desktop()->rect();
    }
    widget->move(((parentRect.width() - widget->width()) >> 1),
                 ((parentRect.height() - widget->height()) >> 1));
}

const float CommonHelper::getWindowWidthMultiplyingPower()
{
    if(widthMultiplyingPower == 0){
        updateWindowSizeMultiplyingPower();
    }

    return widthMultiplyingPower;
}

const float CommonHelper::getWindowHeightMultiplyingPower()
{
    if(heightMultiplyingPower == 0){
        updateWindowSizeMultiplyingPower();
    }
    return heightMultiplyingPower;
}

void CommonHelper::updateWindowSizeMultiplyingPower()
{
    QSize tempSize = qApp->desktop()->size();
    widthMultiplyingPower = (float)tempSize.width() / (float)WINDOW_BASESIZE_WIDTH;
    heightMultiplyingPower = (float)tempSize.height() / (float)WINDOW_BASESIZE_HEIGHT;
}

#ifdef Q_OS_WIN
bool CommonHelper::getSmallestWindowFromCursor(QRect &smallRect)
{
    HWND hwnd;
    POINT pt;
    // 获得当前鼠标位置
    ::GetCursorPos(&pt);
    // 获得当前位置桌面上的子窗口
    hwnd = ::ChildWindowFromPointEx(::GetDesktopWindow(),pt,CWP_SKIPDISABLED | CWP_SKIPINVISIBLE);
    if(hwnd != NULL){
        HWND tempHwnd;
        tempHwnd = hwnd;
        while(true){
            ::GetCursorPos(&pt);
            ::ScreenToClient(tempHwnd,&pt);
            tempHwnd = ::ChildWindowFromPointEx(tempHwnd,pt,CWP_SKIPINVISIBLE);
            if(tempHwnd == NULL || tempHwnd == hwnd){
                break;
            }
            hwnd = tempHwnd;
        }
        RECT tempWindow;
        ::GetWindowRect(hwnd,&tempWindow);
        smallRect.setRect(tempWindow.left,tempWindow.top,tempWindow.right - tempWindow.left,
                          tempWindow.bottom - tempWindow.top);
        return true;
    }
    return false;
}

bool CommonHelper::getCurrentWindowFromCursor(QRect &currRect)
{
    HWND hwnd;
    POINT pt;
    //获得当前鼠标位置
    ::GetCursorPos(&pt);
    // 获得当前位置桌面上的子窗口
    hwnd = ::ChildWindowFromPointEx(::GetDesktopWindow(),pt,CWP_SKIPDISABLED | CWP_SKIPINVISIBLE);
    if(hwnd != NULL){
        RECT tempWindow;
        ::GetWindowRect(hwnd,&tempWindow);
        currRect.setRect(tempWindow.left,tempWindow.top,tempWindow.right - tempWindow.left,
                         tempWindow.bottom - tempWindow.top);
        return true;
    }
    return false;
}


#endif

} // namespace zsj


