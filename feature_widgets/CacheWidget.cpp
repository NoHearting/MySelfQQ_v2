#include "feature_widgets/CacheWidget.h"

#include <QPainter>
#include <QPen>
#include <QBrush>

CacheWidget::CacheWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint |
                         Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_StaticContents);

    borderColor = QColor(Qt::red);
    borderWidth = 4;

    painter = new QPainter;

}

void CacheWidget::showWidget(QWidget *innerWidget)
{
    QRect rect = innerWidget->geometry();
    this->setGeometry(rect.x(),rect.y(),
                      rect.width(),rect.height());
    this->show();
}

void CacheWidget::paintEvent(QPaintEvent *event)
{
    painter->begin(this);
    painter->setBrush(QBrush(borderColor));
    painter->setPen(QPen(Qt::white));
    painter->drawRect(0,0,width(),borderWidth); // top
    painter->drawRect(0,height() - borderWidth,width(),borderWidth); // bottom
    painter->drawRect(0,borderWidth,borderWidth,height() - 2 * borderWidth); // left
    painter->drawRect(width() - borderWidth,borderWidth,borderWidth,height() - 2 * borderWidth); //right
    painter->end();

    QWidget::paintEvent(event);
}

void CacheWidget::setBorderColor(const QColor &value)
{
    borderColor = value;
    brush.setColor(borderColor);
}

void CacheWidget::setBorderWidth(int value)
{
    borderWidth = value;
}
