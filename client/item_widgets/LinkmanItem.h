#ifndef LINKMANITEM_H
#define LINKMANITEM_H

#include "main/Data.h"

#include <QSharedPointer>
#include <memory>
#include <QWidget>


class LinkmanItem : public QWidget
{
    QOBJECT_H
public:
    LinkmanItem(QWidget * parent = nullptr);

    virtual ~LinkmanItem(){}

    virtual std::shared_ptr<zsj::Data> getData()const = 0;
private:
};



#endif // LINKMANITEM_H
