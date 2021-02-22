#include "customer_widgets/MyToolButton.h"

#include <QDebug>

MyToolButton::MyToolButton(QWidget *parent) : QToolButton(parent)
{

}

void MyToolButton::enterEvent(QEvent *)
{
    emit sigEnter();
}

void MyToolButton::leaveEvent(QEvent *)
{
    emit sigLeave();
}
