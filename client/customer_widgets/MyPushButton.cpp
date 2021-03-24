#include "MyPushButton.h"

#include <QDebug>

QVector<QPushButton *> MyPushButton::buttons;

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

    buttons.append(this);
}

void MyPushButton::setChecked(bool check)
{
    if(check)
    {
        for(auto &item : buttons)
        {
             (*item).setChecked(false);
        }
    }
    QPushButton::setChecked(check);
}
