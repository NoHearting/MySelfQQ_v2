#include "StringUserData.h"

StringUserData::StringUserData(const QString &string)
    : QObjectUserData(),data(string)
{

}

QString StringUserData::getData() const
{
    return data;
}

void StringUserData::setData(const QString &value)
{
    data = value;
}
