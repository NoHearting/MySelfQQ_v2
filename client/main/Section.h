#ifndef SECTION_H
#define SECTION_H

#include <QString>
#include <memory>

namespace zsj {


class Section
{
public:
    typedef std::shared_ptr<Section> ptr;

    Section();
    Section(quint64 id,QString sectionName,quint64 belong,int size,bool type);

    Section(const Section & section);

    Section & operator =(const Section & section);

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

private:
    quint64 id;
    QString sectionName;
    quint64 belong;
    int size;
    bool type;
};


} // namespace zsj

#endif // SECTION_H
