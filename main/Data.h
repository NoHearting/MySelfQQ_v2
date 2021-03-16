#ifndef DATA_H
#define DATA_H

#include "utils/Global.h"

#include <memory>
#include <QPixmap>
#include <QSharedPointer>

namespace zsj
{

class Data
{
public:
    typedef std::shared_ptr<Data> ptr;
    Data(global::DataType dataType,const QPixmap & head,
         const QString & nickname,const QString & id,
         const QString & explain = "",bool vip = false);
    virtual ~Data() = 0;

    const QString getName()const
    {
        return nickname;
    }

    const QString getAccount()const{
        return id;
    }

    QPixmap getHead()const{
        if(head.isNull()){
            return QPixmap(global::DefaultHead);
        }
        return head;
    }
    global::DataType getDataType() const;

    QString  getExplain()const{return explain;}

    bool getVip()const{return vip;}


    virtual QString toString();
private:
    /// 数据类型
    global::DataType dataType;

    /// 头像
    QPixmap head;

    /// 昵称
    QString nickname;

    /// 账号id
    QString id;

    /// 签名/说明
    QString explain;

    /// 是否vip
    bool vip;
};

}


#endif // DATA_H
