/**
  * @brief 无边框可拉伸可移动窗口类
  *
  * 可以使用setWidget(QWidget * value)来设置一个窗口为无边框、可拉伸、可移动的
  *
  * @author zsj
  * @date 2020年12月23日19:20:21
  */
#ifndef FRAMELESS_H
#define FRAMELESS_H

#include <QObject>
#include <QRect>
#include <QPoint>

#include "CacheWidget.h"

namespace zsj
{

class Frameless : public QObject
{
    Q_OBJECT
public:
    explicit Frameless(QObject *parent = 0);

    /// @brief 设置边距
    /// 这个边距是用来感应鼠标，从什么地方就可以对窗口进行拉伸
    ///
    /// @param[in] 边距值
    void setPadding(int value);

    /// @brief 设置是否可移动
    /// @param[in] value 是否可移动
    void setMoveEnable(bool value);

    /// @brief 设置是否可拉伸
    /// @param[in] value 是否可拉伸
    void setResizeEnable(bool value);

    /// @brief 设置需要处理的窗口
    /// @param[in] value 窗口
    void setWidget(QWidget *value);

protected:
    bool eventFilter(QObject *, QEvent *);
private:
    /// @brief 初始化拉伸窗口需要的感应鼠标的范围
    /// 8个矩形，鼠标形状在这几个矩形之内会变化
    void initResizeCursorArea();

    /// @brief 设置鼠标的形状，当鼠标坐标落在上述8个矩形内时
    /// @param[in] point 鼠标的坐标
    void setResizeCursor(QPoint point);

    /// @brief 拉伸窗口
    /// @param[in] offsetX x轴偏移量
    /// @param[in] offsetY y轴偏移量
    void resizeWindow(int offsetX,int offsetY);

    /// @brief 移动窗口
    /// @param[in] offsetX x轴偏移量
    /// @param[in] offsetY y轴偏移量
    void moveWindow(int offsetX,int offsetY);
    /// @brief 判断鼠标位置是否落在8个矩形之内
    void judgeMousePos();
private:
    int padding;                    //边距
    bool moveEnable;               //可移动
    bool resizeEnable;              //可拉伸
    QWidget *widget;                //无边框窗体

    bool pressed;                   //鼠标按下
    bool pressedLeft;               //鼠标按下左侧
    bool pressedRight;              //鼠标按下右侧
    bool pressedTop;                //鼠标按下上侧
    bool pressedBottom;             //鼠标按下下侧
    bool pressedLeftTop;            //左上侧
    bool pressedLeftBottom;         //左下
    bool pressedRightTop;           //右上
    bool pressedRightBottom;        //右下

    int rectX, rectY, rectW, rectH; //窗体坐标+宽高
    QPoint lastPos;                 //鼠标按下处坐标

    QRect rectLeft;                 //左侧区域
    QRect rectRight;                //右侧区域
    QRect rectTop;                  //上侧区域
    QRect rectBottom;               //下侧区域
    QRect rectLeftTop;              //左上侧区域
    QRect rectRightTop;             //右上侧区域
    QRect rectLeftBottom;           //左下侧区域
    QRect rectRightBottom;          //右下侧区域


    ///  缓冲窗口
    /// 移动和重绘后先显示此窗口预览效果
    CacheWidget * cacheWidget = nullptr;
signals:
public slots:
};

}

#endif // FRAMELESS_H
