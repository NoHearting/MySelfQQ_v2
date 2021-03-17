#include "GroupData.h"

#include "utils/Util.h"

namespace zsj
{

GroupData::GroupData(const QPixmap &groupHead, const QString &groupName,
                     quint64 groupAccount, const QString &groupIntroduce,
                     quint16 groupUserCount, quint16 groupUserCountMax, bool vip)
    : Data(zsj::global::DataType::GROUP_DATA, groupHead,
           groupName, groupAccount, groupIntroduce, vip),
      userCount(groupUserCount),
      userCountMax(groupUserCountMax)
{
    QPixmap head = getHead();
    zsj::checkAndSetPixmap(head, zsj::global::DefaultHead);
}

QString GroupData::toString()
{
    return QString("GroupData{head:%1,groupName:%2,groupAccount:%3,groupIntroduce:%4,"
                   "userCount:%5,userCountMax:%6,isVip:%7}").arg(getHead().isNull()).arg(getName())
           .arg(getAccount()).arg(getExplain()).arg(userCount).arg(userCountMax).arg(getVip());
}




quint16 GroupData::getUserCount() const
{
    return userCount;
}

void GroupData::setUserCount(const quint16 &value)
{
    userCount = value;
}

quint16 GroupData::getUserCountMax() const
{
    return userCountMax;
}

void GroupData::setUserCountMax(const quint16 &value)
{
    userCountMax = value;
}


}
