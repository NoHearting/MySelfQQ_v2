#include "Amplifier.h"
#include "CommonHelper.h"

#include <QPixmap>
#include <QPainter>

#include <QDebug>

namespace zsj {



Amplifier::Amplifier(pixPtr originPainting, QWidget *parent)
    : QWidget(parent), originPainting(originPainting)
{
    // 设置成无边框对话框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    // 开启鼠标实时追踪
    setMouseTracking(true);

    // 设置默认大小
    this->sideLength = 122 * CommonHelper::getWindowHeightMultiplyingPower();
    this->imageHeight = 90 * CommonHelper::getWindowWidthMultiplyingPower();
    setFixedSize(sideLength, sideLength);

    // 默认隐藏
    hide();
}

void Amplifier::slotSizeChange(int width, int height)
{
    screenSize = QSize(width, height);
}

void Amplifier::slotPositionChange(int xPos, int yPos)
{
    cursorPoint = QPoint(xPos, yPos);
    this->raise();
    int destX = xPos + 4;
    int destY = yPos + 26;

    // 超出屏幕检测
    const QSize parentSize = parentWidget()->size();
    if(destY + height() > parentSize.height())
    {
        destY = yPos - 26 - height();
    }
    if(destX + width() > parentSize.width())
    {
        destX = xPos - 4 - width();
    }
    move(destX, destY);
}

void Amplifier::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 绘制背景
    painter.fillRect(this->rect(), QColor(0, 0, 0, 160));

    QPixmap endPointImage;
    // 绘制放大图
    const QSize parentSize = parentWidget()->size();

    /**
     * @bug   : 在屏幕边缘绘制放大图时会出现图片拉伸
     *          这里暂时做了边缘检测，若是屏幕边缘则不进行放大图的绘制，和QQ截图的采取方式是一致的。
     *
     * @remark: 颜色还是照样识别，但是局部放大的效果暂时禁用
     *
     * @note  : 解决方法，可以发现边缘时，将不能放大的地方，不描绘，或填充黑色，以避免图片被非预期的拉伸问题。
     */
    if((cursorPoint.x() + 15 < parentSize.width() && cursorPoint.x() - 15 > 0)
            && (cursorPoint.y() + 11 < parentSize.height() && cursorPoint.y() - 11 > 0))
    {
        endPointImage = originPainting->copy(
                            QRect(cursorPoint.x() - 15, cursorPoint.y() - 11, 30, 22))
                .scaled(sideLength,imageHeight);
        painter.drawPixmap(0, 0, endPointImage);
    }
    else
    {
        endPointImage = originPainting->copy(cursorPoint.x() - 15, cursorPoint.y() - 11, 30, 22);
    }

    // 绘制十字
    painter.setPen(QPen(QColor(0, 180, 255, 180), 4));
    // 竖线
    painter.drawLine(QPoint(sideLength >> 1, 0), QPoint(sideLength >> 1, imageHeight - 4));
    // 横线
    painter.drawLine(QPoint(0, imageHeight >> 1), QPoint(sideLength, imageHeight >> 1));

    // 绘制大图内边框
    painter.setPen(QPen(Qt::white, 2));
    painter.drawRect(2, 2, width() - 4, imageHeight - 4);

    // 绘制外边框
    painter.setPen(QPen(Qt::black, 1));
    painter.drawRect(0, 0, width() - 1, height() - 1);

    // 当前选中矩形的宽高信息
    QString selectScreenInfo = QString("%1 x %2")
            .arg(screenSize.width()).arg(screenSize.height());

    // 当前鼠标像素值的RGB信息
    QImage image = originPainting->toImage();
    QColor cursorPixel = image.pixel(cursorPoint);
    QString selecctPtRGB = QString("RGB:(%1,%2,%3)")
            .arg(cursorPixel.red())
            .arg(cursorPixel.green())
            .arg(cursorPixel.blue());

    // 绘制坐标轴相关数据
    painter.setPen(Qt::white);
    painter.drawText(QPoint(6,imageHeight + 14),selectScreenInfo);
    painter.drawText(QPoint(6,imageHeight + 27),selecctPtRGB);

    QWidget::paintEvent(event);

}
} // namespace zsj

