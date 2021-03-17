#include "UserData.h"

#include "utils/Util.h"
#include <QDebug>

namespace zsj
{


UserData::UserData() :
    Data(zsj::global::DataType::SYSTEM_DATA,QPixmap(""),"",0,"",false),
    remark(""),level(-1)
{

}

UserData::UserData(const QPixmap &head, const QString &nickname,
                   quint64 account, const QString &signature,
                   const QString &remark, bool isVip, quint8 level)
    : Data(zsj::global::DataType::USER_DATA, head,
           nickname, account, signature, isVip),
      remark(remark), level(level)
{
}

QString UserData::toString()
{
    return QString("UserData{%1,remark:%2,level:%3").arg(Data::toString())
            .arg(remark).arg(level);
}


}
