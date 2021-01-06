#include "ReadQStyleSheet.h"

#include <QDebug>
#include <QTextStream>
#include <QStringList>

namespace zsj
{


ReadQStyleSheet::ReadQStyleSheet()
{

}

QString ReadQStyleSheet::readQss(QString filePath)
{
    QFile file(filePath);
    QString qss;
    if(file.open(QIODevice::ReadOnly))
    {
        QStringList list;
        QTextStream in(&file);
        while(!in.atEnd()){
            QString line;
            in >> line;
            list << line;
        }
        qss  = list.join("\n");
        qDebug() << qss;
        file.close();
        return qss;
    }
    else{
        qCritical() << "style file:" << filePath << "not exist";

    }
    return QString("");
}

}
