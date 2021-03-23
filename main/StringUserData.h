#ifndef STRINGUSERDATA_H
#define STRINGUSERDATA_H

#include <QObjectUserData>
#include <QString>

class StringUserData : public QObjectUserData
{
public:
    StringUserData(const QString & string);

    QString getData() const;
    void setData(const QString &value);

private:
    QString data;
};

#endif // STRINGUSERDATA_H
