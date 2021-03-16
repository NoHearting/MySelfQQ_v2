/**
  * @brief 群组数据类
  *
  * @author zsj
  * @date 2020年12月23日19:40:17
  */

#ifndef GROUPDATA_H
#define GROUPDATA_H

#include <memory>
#include <QPixmap>
#include <QString>
#include <QSharedPointer>

#include "main/Data.h"

namespace zsj{

class GroupData : public Data
{
public:
    typedef std::shared_ptr<GroupData> ptr;

    GroupData(const QPixmap & groupHead,const QString & groupName,
              const QString & groupAccount,const QString & groupIntroduce,
              quint16 groupUserCount,quint16 groupCountMax,bool vip = false);

    QString toString();


    quint16 getUserCount() const;
    void setUserCount(const quint16 &value);

    quint16 getUserCountMax() const;
    void setUserCountMax(const quint16 &value);

private:
    quint16 userCount;    /// 用户数
    quint16 userCountMax;   /// 用户数最大值
};

}
#endif // GROUPDATA_H
