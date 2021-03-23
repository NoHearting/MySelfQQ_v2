/**
  * @brief 用户数据
  *
  * @author zsj
  * @date 2020年12月23日20:33:33
  */
#ifndef USERDATA_H
#define USERDATA_H

#include <memory>
#include <QPixmap>
#include <QString>
#include <QSharedPointer>

#include "main/Data.h"

namespace zsj {

class UserData : public Data
{
public:
    typedef std::shared_ptr<UserData> ptr;
    UserData();
    UserData(const QPixmap & head,const QString & nickname,quint64 account,
             const QString & signature,const QString & remark,
             bool isVip = false,quint8 level = 0);


    QString toString();

    // getter
    QString getRemark()const{return remark;}
    quint8 getLevel()const{return level;}

//    // setter
//    void setHead(const QPixmap & head){this->head = head;}
//    void setNickname(const QString & nickname){this->nickname = nickname;}
//    void setAccount(const QString & account){this->account = account;}
//    void setSignature(const QString & signature){this->signature = signature;}
//    void setRemark(const QString & remark){this->remark = remark;}
//    void setVip(bool vip){this->vip = vip;}
//    void setLevel(quint8 level){this->level = level;}

private:

    QString remark;     /// 备注

    quint8 level;       /// 等级

};

} // namespace zsj



#endif // USERDATA_H
