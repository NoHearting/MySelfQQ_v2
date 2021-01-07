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

#include "Data.h"

namespace zsj{

class GroupData : public Data
{
public:
    typedef std::shared_ptr<GroupData> ptr;

    GroupData();
    GroupData(const QPixmap & groupHead,const QString & groupName,
              const QString & groupAccount,const QString & groupIntroduce,
              quint16 groupUserCount,quint16 groupCountMax,bool vip = false);

    QString toString();

    const QPixmap getHead() const override;
    void setHead(const QPixmap &value);

    const QString getName() const override;
    void setName(const QString &value);

    const QString getAccount() const override;
    void setAccount(const QString &value);

    QString getIntroduce() const;
    void setIntroduce(const QString &value);

    quint16 getUserCount() const;
    void setUserCount(const quint16 &value);

    quint16 getUserCountMax() const;
    void setUserCountMax(const quint16 &value);

    bool getVip() const;
    void setVip(bool value);

private:
    QPixmap head;       /// 群头像
    QString name;       /// 群名
    QString account;    /// 群号
    QString introduce;  /// 群介绍
    quint16 userCount;    /// 用户数
    quint16 userCountMax;   /// 用户数最大值

    bool vip;           /// 是否vip群
};

}
#endif // GROUPDATA_H
