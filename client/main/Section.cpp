#include "Section.h"

namespace zsj {



Section::Section() :
    Section(0,"",0,0,false)
{

}

Section::Section(quint64 id, QString sectionName, quint64 belong,
                 int size, bool type) :
    id(id),sectionName(sectionName),belong(belong),size(size),type(type)
{

}

Section::Section(const Section &section)
{
    *this = section;
}

Section & Section::operator =(const Section &section)
{
    if(this == &section){
        return *this;
    }
    this->id = section.id;
    this->sectionName = section.sectionName;
    this->belong = section.belong;
    this->size = section.size;
    this->type = section.type;
}

quint64 Section::getId() const
{
    return id;
}

void Section::setId(const quint64 &value)
{
    id = value;
}

QString Section::getSectionName() const
{
    return sectionName;
}

void Section::setSectionName(const QString &value)
{
    sectionName = value;
}

quint64 Section::getBelong() const
{
    return belong;
}

void Section::setBelong(const quint64 &value)
{
    belong = value;
}

int Section::getSize() const
{
    return size;
}

void Section::setSize(int value)
{
    size = value;
}

bool Section::getType() const
{
    return type;
}

void Section::setType(bool value)
{
    type = value;
}

} // namespace zsj
