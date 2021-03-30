#ifndef SECTIONDATA_H
#define SECTIONDATA_H

#include <QString>
#include "main/Data.h"
#include "main/Section.h"
#include <QVector>

namespace zsj {

class SectionData
{
public:
    SectionData();

    SectionData(const Section & section);


    quint64 getId() const;
    void setId(const quint64 &value);

    QString getSectionName() const;
    void setSectionName(const QString &value);

    quint64 getBelong() const;
    void setBelong(const quint64 &value);

    int getSize() const;
    void setSize(int value);

    bool getType() const;
    void setType(bool value);

    QVector<zsj::Data::ptr> getItems() const;
    void setItems(const QVector<zsj::Data::ptr> &value);

    Section getSection() const;
    void setSection(const Section &value);

private:
    Section section;
    QVector<zsj::Data::ptr> items;
};

} // namespace zsj

#endif // SECTIONDATA_H
