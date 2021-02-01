#include "feature_widgets/FloatScrollBar.h"

#include <QDebug>

FloatScrollBar::FloatScrollBar(Qt::Orientation orientation, QWidget *parent) : QScrollBar(parent)
{
    this->setOrientation(orientation);
    this->setRange(0, 0);
    this->hide();

}


void FloatScrollBar::setQss(const QString &qss)
{
    this->setStyleSheet(qss);
}

void FloatScrollBar::valueChangedFloat(int value)
{
    this->setValue(value);
}

void FloatScrollBar::rangeChangedFloat(int min, int max)
{
    this->setMinimum(min);
    this->setRange(0, max);
    this->setPageStep(0.75 * (this->height() + max));
    if(max <= 0)
    {
        this->hide();
    }
    else{
        this->show();
    }
}
