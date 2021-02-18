#pragma once

#include <QSharedPointer>
#include <QWidget>
#include <QPixmap>

typedef QSharedPointer<QPixmap> pixPtr;


namespace zsj {



/**
 * @brief 放大取色器
 * @note 关于鼠标位置局部放大的操作以及色卡取值的操作
 */
class Amplifier : public QWidget
{
    Q_OBJECT
public:
    typedef QSharedPointer<Amplifier> ptr;
    explicit Amplifier(pixPtr originPainting, QWidget *parent = 0);

public slots:
    /**
     * @brief 大小修改
     * @param width 宽
     * @param height 高
     */
    void slotSizeChange(int width,int height);

    /**
     * @brief 位置修改
     * @param xPos x坐标
     * @param yPos y坐标
     */
    void slotPositionChange(int xPos,int yPos);

protected:
    void paintEvent(QPaintEvent *event);

private:
    /// 外部组件的大小信息
    QSize screenSize;

    /// 鼠标的位置
    QPoint cursorPoint;

    /// 取色放大器的变长
    int sideLength;

    /// 放大区的高度
    int imageHeight;

    /// 屏幕原画
    pixPtr originPainting;


};
} // namespace zsj
