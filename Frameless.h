#ifndef FRAMELESS_H
#define FRAMELESS_H

#include <QObject>
#include <QRect>
#include <QPoint>

namespace Zsj {

class Frameless : public QObject
{
    Q_OBJECT
public:
    explicit Frameless(QObject *parent = 0);

    void setPadding(int value);

    void setMoveEnable(bool value);

    void setResizeEnable(bool value);

    void setWidget(QWidget *value);

protected:
    bool eventFilter(QObject *, QEvent *);
private:
    int padding;                    //边距
    bool moveEnable;               //可移动
    bool resizeEnable;              //可拉伸
    QWidget * widget;               //无边框窗体

    bool pressed;                   //鼠标按下
    bool pressedLeft;               //鼠标按下左侧
    bool pressedRight;              //鼠标按下右侧
    bool pressedTop;                //鼠标按下上侧
    bool pressedBottom;             //鼠标按下下侧
    bool pressedLeftTop;            //左上侧
    bool pressedLeftBottom;         //左下
    bool pressedRightTop;           //右上
    bool pressedRightBottom;        //右下

    int rectX,rectY,rectW,rectH;    //窗体坐标+宽高
    QPoint lastPos;                 //鼠标按下处坐标

    QRect rectLeft;                 //左侧区域
    QRect rectRight;                //右侧区域
    QRect rectTop;                  //上侧区域
    QRect rectBottom;               //下侧区域
    QRect rectLeftTop;              //左上侧区域
    QRect rectRightTop;             //右上侧区域
    QRect rectLeftBottom;           //左下侧区域
    QRect rectRightBottom;          //右下侧区域

signals:

public slots:
};

}

#endif // FRAMELESS_H
