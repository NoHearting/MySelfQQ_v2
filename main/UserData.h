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

#include "main/Data.h"

namespace zsj {

class UserData : public Data
{
public:
    typedef std::shared_ptr<UserData> ptr;
    UserData();
    UserData(const QPixmap & head,const QString & nickname,const QString & account,
             const QString & signature,const QString & remark,
             bool isVip = false,quint8 level = 0);


    QString toString();

    // getter
    const QPixmap getHead()const override{return head;}
    const QString getNickname()const{return nickname;}
    const QString getAccount()const override{return account;}
    const QString getName()const override{return nickname;}
    QString getSignature()const{return signature;}
    QString getRemark()const{return remark;}
    bool isVip()const{return vip;}
    quint8 getLevel()const{return level;}

    // setter
    void setHead(const QPixmap & head){this->head = head;}
    void setNickname(const QString & nickname){this->nickname = nickname;}
    void setAccount(const QString & account){this->account = account;}
    void setSignature(const QString & signature){this->signature = signature;}
    void setRemark(const QString & remark){this->remark = remark;}
    void setVip(bool vip){this->vip = vip;}
    void setLevel(quint8 level){this->level = level;}
private:
    QPixmap head;       /// 头像
    QString nickname;   /// 昵称
    QString account;    /// 账号
    QString signature;  /// 签名
    QString remark;     /// 备注

    /// 扩展属性，后面可能会用
    bool vip;         /// 是否vip
    quint8 level;       /// 等级

};

} // namespace zsj



#endif // USERDATA_H