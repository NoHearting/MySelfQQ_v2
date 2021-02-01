#include "Frameless.h"

#include <QEvent>
#include <QWidget>
#include <QEvent>
#include <QHoverEvent>
#include <QDebug>

namespace zsj
{

Frameless::Frameless(QObject *parent) : QObject(parent)
{
    padding = 8;
    moveEnable = true;
    resizeEnable = true;
    widget = nullptr;
    isMoved = false;

    pressed = false;
    pressedLeft = false;
    pressedRight = false;
    pressedTop = false;
    pressedBottom = false;
    pressedLeftTop = false;
    pressedRightTop = false;
    pressedLeftBottom = false;
    pressedRightBottom = false;

    cacheWidget = new CacheWidget;

    //如果父类是窗体则直接设置
    if(parent->isWidgetType())
    {
        setWidget((QWidget *)parent);
    }
}

bool Frameless::eventFilter(QObject *watched, QEvent *event)
{
    if(nullptr != widget && watched == widget)
    {
        if(event->type() == QEvent::Resize)
        {
            initResizeCursorArea();
        }
        else if(event->type() == QEvent::HoverMove)
        {
            //设置对应鼠标形状，这个必须放在这里而不是下面，因为可以在鼠标没有按下时识别
            QHoverEvent *hoverEvent = (QHoverEvent *)event;
            QPoint point = hoverEvent->pos();

            setResizeCursor(point);

            //根据当前鼠标位置，计算xy轴移动了多少
            int offsetX = point.x() - lastPos.x();
            int offsetY = point.y() - lastPos.y();

            // 偏移量不能为0
            if(offsetX != 0 || offsetY != 0 )
            {
                //根据按下处的位置判断是否移动空间还是拉伸控件
                moveWindow(offsetX, offsetY);
                resizeWindow(offsetX, offsetY);
            }

        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            //记住当前空间坐标和宽高以及鼠标按下的坐标
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            rectX = widget->x();
            rectY = widget->y();
            rectW = widget->width();
            rectH = widget->height();
            lastPos = mouseEvent->pos();

            //判断按下的手柄的区域位置
            judgeMousePos();
            cacheWidget->showWidget(widget);

        }
        else if(event->type() == QEvent::MouseMove)
        {
            //改成用HoverMove识别
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {

            if(cacheWidget->isVisible())
            {
                cacheWidget->hide();
                auto geo = cacheWidget->geometry();
                widget->setGeometry(geo);
                if(isResize)
                {
                    // 设置两次是为了解决聊天窗口（ChatWidget）的聊天记录的大小在窗口变化的时候不跟着变化
                    // 只有再次改变窗口大小才跟着变化，所以这里多设置一次
                    // 权宜之计
                    widget->setGeometry(geo.x(), geo.y(), geo.width() + 1, geo.height() + 1);
                    qDebug() << "move once";
                }
            }

            //恢复所有
            isMoved = false;
            pressed = false;
            pressedLeft = false;
            pressedRight = false;
            pressedTop = false;
            pressedBottom = false;
            pressedLeftTop = false;
            pressedRightTop = false;
            pressedLeftBottom = false;
            pressedRightBottom = false;
            widget->setCursor(Qt::ArrowCursor);

        }
    }
    return QObject::eventFilter(watched, event);
}

void Frameless::initResizeCursorArea()
{
    //重新计算八个描点的区域，描点区域的作用还有就是计算鼠标坐标是否在某一个区域内
    int width = widget->width();
    int height = widget->height();

    //左描点区域
    rectLeft = QRect(0, padding, padding, height - padding * 2);
    //上描点区域
    rectTop = QRect(padding, 0, width - padding * 2, padding);
    //右侧描点区域
    rectRight = QRect(width - padding, padding, padding, height - padding * 2);
    //下侧描点区域
    rectBottom = QRect(padding, height - padding, width - padding * 2, padding);

    //左上角描点区域
    rectLeftTop = QRect(0, 0, padding, padding);
    //右上角描点区域
    rectRightTop = QRect(width - padding, 0, padding, padding);
    //左下角描点区域
    rectLeftBottom = QRect(0, height - padding, padding, padding);
    //右下角描点区域
    rectRightBottom = QRect(width - padding, height - padding, padding, padding);
}

void Frameless::setResizeCursor(QPoint point)
{
    if(resizeEnable)
    {
        if(rectLeft.contains(point))
        {
            widget->setCursor(Qt::SizeHorCursor);
        }
        else if(rectRight.contains(point))
        {
            widget->setCursor(Qt::SizeHorCursor);
        }
        else if(rectBottom.contains(point))
        {
            widget->setCursor(Qt::SizeVerCursor);
        }
        else if(rectTop.contains(point))
        {
            widget->setCursor(Qt::SizeVerCursor);
        }
        else if(rectLeftTop.contains(point))
        {
            widget->setCursor(Qt::SizeFDiagCursor);
        }
        else if(rectRightTop.contains(point))
        {
            widget->setCursor(Qt::SizeBDiagCursor);
        }
        else if(rectLeftBottom.contains(point))
        {
            widget->setCursor(Qt::SizeBDiagCursor);
        }
        else if(rectRightBottom.contains(point))
        {
            widget->setCursor(Qt::SizeFDiagCursor);
        }
        else
        {
            widget->setCursor(Qt::ArrowCursor);
        }
    }

}

void Frameless::moveWindow(int offsetX, int offsetY)
{
    if(moveEnable)
    {
        if(pressed)
        {
            isMoved = true;
            cacheWidget->move(widget->x() + offsetX, widget->y() + offsetY);
        }
    }
}


void Frameless::judgeMousePos()
{
    if(rectLeft.contains(lastPos))
    {
        pressedLeft = true;
    }
    else if(rectRight.contains(lastPos))
    {
        pressedRight = true;
    }
    else if(rectTop.contains(lastPos))
    {
        pressedTop = true;
    }
    else if(rectBottom.contains(lastPos))
    {
        pressedBottom = true;
    }
    else if(rectLeftTop.contains(lastPos))
    {
        pressedLeftTop = true;
    }
    else if(rectRightTop.contains(lastPos))
    {
        pressedRightTop = true;
    }
    else if(rectRightBottom.contains(lastPos))
    {
        pressedRightBottom = true;
    }
    else if(rectLeftBottom.contains(lastPos))
    {
        pressedLeftBottom = true;
    }
    else
    {
        pressed = true;
    }
}

void Frameless::resizeWindow(int offsetX, int offsetY)
{
    if(resizeEnable)
    {
        if(pressedLeft)
        {
            int resizeW = widget->width() - offsetX;
            if(widget->minimumWidth() <= resizeW)
            {
                cacheWidget->setGeometry(widget->x() + offsetX, rectY, resizeW, rectH);
                isResize = true;
            }
        }
        else if(pressedRight)
        {
            int resizeW = rectW + offsetX;
            if(widget->minimumWidth() <= resizeW && resizeW <= widget->maximumWidth())
            {
                cacheWidget->setGeometry(rectX, rectY, rectW + offsetX, rectH);
                isResize = true;
            }
        }
        else if(pressedTop)
        {
            int resizeH = widget->height() - offsetY;
            if(widget->minimumHeight() <= resizeH)
            {
                cacheWidget->setGeometry(rectX, widget->y() + offsetY, rectW, resizeH);
                isResize = true;
            }
        }
        else if(pressedBottom)
        {
            int resizeH = rectH + offsetY;
            if(widget->minimumHeight() <= resizeH && resizeH <= widget->maximumHeight())
            {
                cacheWidget->setGeometry(rectX, rectY, rectW, rectH + offsetY);
                isResize = true;
            }
        }
        else if(pressedLeftTop)
        {
            int resizeW = widget->width() - offsetX;
            int resizeH = widget->height() - offsetY;

            int ofsX = offsetX;
            int ofsY = offsetY;

            if(resizeW <= widget->minimumWidth())
            {
                ofsX = offsetX - (widget->minimumWidth() - resizeW);
                resizeW = widget->minimumWidth();
            }
            if(resizeH <= widget->minimumHeight())
            {
                ofsY = offsetY - (widget->minimumHeight() - resizeH);
                resizeH = widget->minimumHeight();
            }


            cacheWidget->setGeometry(widget->x() + ofsX, widget->y() + ofsY, resizeW, resizeH);
            isResize = true;

        }
        else if(pressedRightTop)
        {
            int resizeW = rectW + offsetX;
            int resizeH = widget->height() - offsetY;

            int ofsY = offsetY;

            if(resizeW <= widget->minimumWidth())
            {
                resizeW = widget->minimumWidth();
            }
            if(resizeH <= widget->minimumHeight())
            {
                ofsY = offsetY - (widget->minimumHeight() - resizeH);
                resizeH = widget->minimumHeight();
            }
            cacheWidget->setGeometry(widget->x(), widget->y() + ofsY, resizeW, resizeH);
            isResize = true;

        }
        else if(pressedLeftBottom)
        {
            int resizeW = widget->width() - offsetX;
            int resizeH = rectH + offsetY;


            int ofsX = offsetX;

            if(resizeW <= widget->minimumWidth())
            {
                ofsX = offsetX - (widget->minimumWidth() - resizeW);
                resizeW = widget->minimumWidth();
            }
            if(resizeH <= widget->minimumHeight())
            {
                resizeH = widget->minimumHeight();
            }


            cacheWidget->setGeometry(widget->x() + ofsX, widget->y(), resizeW, resizeH);
            isResize = true;
        }
        else if(pressedRightBottom)
        {
            int resizeW = rectW + offsetX;
            int resizeH = rectH + offsetY;

            if(resizeW <= widget->minimumWidth())
            {
                resizeW = widget->minimumWidth();
            }
            if(resizeH <= widget->minimumHeight())
            {
                resizeH = widget->minimumHeight();
            }
            cacheWidget->setGeometry(widget->x(), widget->y(), resizeW, resizeH);
            isResize = true;
        }
    }
}



void Frameless::setPadding(int value)
{
    padding = value;
}

void Frameless::setMoveEnable(bool value)
{
    moveEnable = value;
}

void Frameless::setResizeEnable(bool value)
{
    resizeEnable = value;
}

void Frameless::setWidget(QWidget *value)
{
    if(this->widget == nullptr)
    {
        this->widget = value;
        //设置鼠标追踪为真
        this->widget->setMouseTracking(true);
        //绑定事件过滤器
        this->widget->installEventFilter(this);
        //设置悬停为真，必须设置这个，不然当父窗体里边还有子窗体全部遮挡了识别不到MouseMove，需要识别HoverMove
        this->widget->setAttribute(Qt::WA_Hover, true);
    }
}



}
