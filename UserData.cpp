#include "UserData.h"

#include "Util.h"
#include <QDebug>

namespace zsj
{

UserData::UserData() :
    Data(zsj::global::DataType::USER_DATA),
    head(QPixmap("")), nickname(""),
    account(""), signature(""),
    remark(""), vip(false), level(0)
{

}


UserData::UserData(const QPixmap &head, const QString &nickname,
                   const QString &account, const QString &signature,
                   const QString &remark, bool isVip, quint8 level)
    : Data(zsj::global::DataType::USER_DATA),
      head(head), nickname(nickname), account(account)
    , signature(signature), remark(remark), vip(isVip), level(level)
{
    zsj::checkAndSetPixmap(this->head, zsj::global::defaultHead);
}

QString UserData::toString()
{
    return QString("UserData{head:%1,nickname:%2,account:%3,signature:%4,"
                   "remark:%5,vip:%6,level:%7}").arg(head.isNull()).arg(nickname)
           .arg(account).arg(signature).arg(remark).arg(vip).arg(level);
}


}
