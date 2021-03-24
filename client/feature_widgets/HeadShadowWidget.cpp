#include "feature_widgets/HeadShadowWidget.h"

#include <QPainter>
#include <QRadialGradient>
#include <QPaintEvent>

HeadShadowWidget::HeadShadowWidget(QWidget *parent) : QWidget(parent)
{

}

void HeadShadowWidget::paintEvent(QPaintEvent *)
{
    // 在头像周围画阴影
    QPainter * painter = new QPainter;
    painter->begin(this);
    QRadialGradient radg2(40,40,40,40,40);
    radg2.setColorAt(0,Qt::white);
    radg2.setColorAt(0.8,Qt::white);
    radg2.setColorAt(0.81,QColor(18,183,245,100));
    radg2.setColorAt(1.0,QColor(195,234,249,50));
    painter->setPen(Qt::transparent);
    painter->setBrush(radg2);
    painter->drawEllipse(0,0,80,80);
    painter->end();
}

