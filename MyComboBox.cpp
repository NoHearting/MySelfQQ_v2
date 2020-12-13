#include "MyComboBox.h"

#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QDebug>

MyComboBox::MyComboBox(QWidget *parent) : QComboBox(parent)
{

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

