#include "Data.h"


namespace zsj {

Data::Data(global::DataType dataType,
           const QPixmap &head,
           const QString &nickname,
           const QString &id,
           const QString &explain, bool vip) :
    dataType(dataType),
    head(head),
    nickname(nickname),
    id(id),
    explain(explain),
    vip(vip)
{

}

global::DataType Data::getDataType() const
{
    return dataType;
}

QString Data::toString()
{
    return QString("Data{dataType:%1,head:%2,nickname:%3,id:%4,explain:%5,vip:%6}")
            .arg((dataType == global::DataType::GROUP_DATA) ? "GROUP_DATA" : "USER_DATA")
            .arg(head.isNull()).arg(nickname).arg(id).arg(explain).arg(vip);
}


Data::~Data()
{

}

}


