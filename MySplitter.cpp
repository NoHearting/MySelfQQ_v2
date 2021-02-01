#include "MySplitter.h"

#include <QDebug>

MySplitter::MySplitter(QWidget *parent) : QSplitter(parent)
{

}

void MySplitter::moveSplitter(int pos, int index)
{
    qDebug() << "moveSplitter";
    QSplitter::moveSplitter(pos,index);
}
