#include "customer_widgets/MyComboBox.h"

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QDebug>

#include "utils/Util.h"

MyComboBox::MyComboBox(QWidget *parent) : QComboBox(parent)
{

}

MyComboBox::~MyComboBox()
{
    DESTRUCT_LOG_DEBUG("destruct MyComboBox");
}

void MyComboBox::showPopup()
{
    emit setLineEditCssOn();
    QComboBox::showPopup();
}

void MyComboBox::hidePopup()
{
    emit setLineEditCssOff();
    QComboBox::hidePopup();
}

