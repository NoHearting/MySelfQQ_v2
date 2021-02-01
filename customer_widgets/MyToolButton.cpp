#include "customer_widgets/MyToolButton.h"

#include <QDebug>

MyToolButton::MyToolButton(QWidget *parent) : QToolButton(parent)
{
    //将子组件的鼠标事件向上传递
//    this->setAttribute(Qt::WA_TransparentForMouseEvents);

//    this->setMouseTracking(true);
}
