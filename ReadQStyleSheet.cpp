#include "ReadQStyleSheet.h"


namespace Zsj {


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
    return QString("");
}

}
