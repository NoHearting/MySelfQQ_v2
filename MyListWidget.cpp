#include "MyListWidget.h"
#include "ReadQStyleSheet.h"

#include <QDebug>

MyListWidget::MyListWidget(QWidget *parent)
    : QListWidget(parent)
    , verticalScrollBarWidth(8)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    floatScrollBar = new FloatScrollBar(Qt::Vertical,this);
    connect(this->verticalScrollBar(),&QScrollBar::valueChanged,floatScrollBar,&FloatScrollBar::valueChangedFloat);
    connect(floatScrollBar,&FloatScrollBar::valueChanged,this,&MyListWidget::valueChanged);
    connect(this->verticalScrollBar(),&QScrollBar::rangeChanged,floatScrollBar,&FloatScrollBar::rangeChangedFloat);

    setScrollBarQss(zsj::ReadQStyleSheet::readQss("://css/scrollBar.css"));
}

void MyListWidget::setScrollBarQss(const QString &qss)
{
    floatScrollBar->setQss(qss);
}

void MyListWidget::addItem(QListWidgetItem *item)
{
    QListWidget::addItem(item);

    // 添加项目的时候发送一个信号
    emit sigAddItem(item);
}

QListWidgetItem * MyListWidget::takeItem(int row)
{
    auto item = QListWidget::takeItem(row);

    // 移除元素时发送一个信号
    emit sigTakeItem();

    return item;
}


void MyListWidget::resizeEvent(QResizeEvent *e)
{
    int posX = this->width() - this->verticalScrollBarWidth;
    this->floatScrollBar->setGeometry(posX, 8, this->verticalScrollBarWidth, this->height() - 2);
    return QListWidget::resizeEvent(e);
}

void MyListWidget::enterEvent(QEvent *e)
{
    if(this->floatScrollBar->maximum() > 0){
        this->floatScrollBar->show();
    }
    return QListWidget::enterEvent(e);
}

void MyListWidget::leaveEvent(QEvent *e)
{
    this->floatScrollBar->hide();
    return QListWidget::leaveEvent(e);
}

void MyListWidget::valueChanged(int value)
{
    this->verticalScrollBar()->setValue(value);
}

