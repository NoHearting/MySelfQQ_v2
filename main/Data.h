#ifndef DATA_H
#define DATA_H

#include "utils/Global.h"

#include <memory>
#include <QPixmap>

namespace zsj
{

class Data
{
public:
    typedef std::shared_ptr<Data> ptr;
    Data(zsj::global::DataType dataType = zsj::global::DataType::USER_DATA);
    virtual ~Data() = 0;

    virtual const QString getName()const
    {
        return "origin name";
    }

    virtual const QString getAccount()const{
        return "origin account";
    }

    virtual const QPixmap getHead()const{
        return QPixmap(global::defaultHead);
    }
    global::DataType getDataType() const;

private:
    global::DataType dataType;

};

}


#endif // DATA_H
