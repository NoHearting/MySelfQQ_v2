#include "GroupData.h"

#include "Util.h"

namespace zsj{

GroupData::GroupData()
    :head(""),name(""),account("")
    ,introduce(""),userCount(0)
    ,userCountMax(0),vip(false)
{

}

GroupData::GroupData(const QPixmap &groupHead, const QString &groupName,
                     const QString &groupAccount, const QString &groupIntroduce,
                     quint16 groupUserCount, quint16 groupUserCountMax, bool vip)
    :head(groupHead),name(groupName),account(groupAccount)
    ,introduce(groupIntroduce),userCount(groupUserCount)
    ,userCountMax(groupUserCountMax),vip(vip)
{
    zsj::checkAndSetPixmap(head,zsj::defaultHead);
}

QString GroupData::toString()
{
    return QString("GroupData{head:%1,groupName:%2,groupAccount:%3,groupIntroduce:%4,"
                   "userCount:%5,userCountMax:%6,isVip:%7}").arg(head.isNull()).arg(name)
            .arg(account).arg(introduce).arg(userCount).arg(userCountMax).arg(vip);
}

QPixmap GroupData::getHead() const
{
    return head;
}

void GroupData::setHead(const QPixmap &value)
{
    head = value;
}

QString GroupData::getName() const
{
    return name;
}

void GroupData::setName(const QString &value)
{
    name = value;
}

QString GroupData::getAccount() const
{
    return account;
}

void GroupData::setAccount(const QString &value)
{
    account = value;
}

QString GroupData::getIntroduce() const
{
    return introduce;
}

void GroupData::setIntroduce(const QString &value)
{
    introduce = value;
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

bool GroupData::getVip() const
{
    return vip;
}

void GroupData::setVip(bool value)
{
    vip = value;
}

}
