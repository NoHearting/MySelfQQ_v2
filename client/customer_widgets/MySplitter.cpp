#include "customer_widgets/MySplitter.h"

#include <QDebug>

MySplitter::MySplitter(QWidget *parent) : QSplitter(parent)
{

}

void MySplitter::moveSplitter(int pos, int index)
{
    QSplitter::moveSplitter(pos,index);
}
