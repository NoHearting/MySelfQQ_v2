#include "ReadQStyleSheet.h"

#include <QDebug>

namespace zsj
{


ReadQStyleSheet::ReadQStyleSheet()
{

}

QString ReadQStyleSheet::readQss(QString filePath)
{
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        QString StyleSheet(file.readAll());
        file.close();
        return StyleSheet;
    }
    else{
        qCritical() << "style file:" << filePath << "not exist";

    }
    return QString("");
}

}
