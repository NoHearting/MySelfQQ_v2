#include "MyTreeWidget.h"
#include "ReadQStyleSheet.h"

#include <QDebug>

MyTreeWidget::MyTreeWidget(QWidget *parent)
    : QTreeWidget(parent)
    , verticalScrollBarWidth(8)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    floatScrollBar = new FloatScrollBar(Qt::Vertical, this);
    connect(this->verticalScrollBar(), &QScrollBar::valueChanged, floatScrollBar, &FloatScrollBar::valueChangedFloat);
    connect(floatScrollBar, &FloatScrollBar::valueChanged, this, &MyTreeWidget::valueChanged);
    connect(this->verticalScrollBar(), &QScrollBar::rangeChanged, floatScrollBar, &FloatScrollBar::rangeChangedFloat);

    setScrollBarQss(zsj::ReadQStyleSheet::readQss("://css/scrollBar.css"));
}

void MyTreeWidget::setScrollBarQss(const QString &qss)
{
    floatScrollBar->setQss(qss);
}


void MyTreeWidget::resizeEvent(QResizeEvent *e)
{
    int posX = this->width() - this->verticalScrollBarWidth;
    this->floatScrollBar->setGeometry(posX, 8, this->verticalScrollBarWidth, this->height() - 2);
    return QTreeWidget::resizeEvent(e);
}

void MyTreeWidget::enterEvent(QEvent *e)
{
    if(this->floatScrollBar->maximum() > 0)
    {
        qDebug() << "true " << this->floatScrollBar->maximum();
        this->floatScrollBar->show();
    }
    return QTreeWidget::enterEvent(e);
}

void MyTreeWidget::leaveEvent(QEvent *e)
{
    this->floatScrollBar->hide();
    return QTreeWidget::leaveEvent(e);
}

void MyTreeWidget::valueChanged(int value)
{
    this->verticalScrollBar()->setValue(value);
}

