#include "SectionData.h"


namespace zsj {

SectionData::SectionData() :
    SectionData(Section())
{

}

SectionData::SectionData(const Section & section) :
    section(section)

{

}

quint64 SectionData::getId() const
{
    return section.getId();
}

void SectionData::setId(const quint64 &value)
{
    section.setId(value);
}

QString SectionData::getSectionName() const
{
    return section.getSectionName();
}

void SectionData::setSectionName(const QString &value)
{
    section.setSectionName(value);
}

quint64 SectionData::getBelong() const
{
    return section.getBelong();
}

void SectionData::setBelong(const quint64 &value)
{
    section.setBelong(value);
}

int SectionData::getSize() const
{
    return section.getSize();
}

void SectionData::setSize(int value)
{
    section.setSize(value);
}

bool SectionData::getType() const
{
    return section.getType();
}

void SectionData::setType(bool value)
{
    section.setType(value);
}

QVector<zsj::Data::ptr> SectionData::getItems() const
{
    return items;
}

void SectionData::setItems(const QVector<zsj::Data::ptr> &value)
{
    items = value;
}

Section SectionData::getSection() const
{
    return section;
}

void SectionData::setSection(const Section &value)
{
    section = value;
}


} // namespace zsj
