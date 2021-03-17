#include "DataBase.h"

#include <QDebug>

namespace zsj
{

DataBase::DataBase(const QString &driverName,
                   const QString &defaultDbName,
                   DBDriverType type) :
    currentDbName(defaultDbName), type(type), driverName(driverName)
{

}

DataBase::DataBase():
    currentDbName(""), type(DBDriverType::UNKNOW), driverName("")
{

}

DataBase::~DataBase()
{

}

bool DataBase::exec(QSqlQuery &query, const QString &dbName)
{

    if(!dbName.isEmpty())
    {
        changeDataBase(dbName);
    }
    if(connected){
        return query.exec();
    }
    else{
        qCritical() << "database not open";
        return false;
    }
}


bool DataBase::selectQuery(QSqlQuery &query, const QString &dbName)
{
    return exec(query, dbName);
}

bool DataBase::deleteQuery(QSqlQuery &query, const QString &dbName)
{
    return exec(query, dbName);
}

bool DataBase::updateQuery(QSqlQuery &query, const QString &dbName)
{
    return exec(query, dbName);
}

bool DataBase::insertQuery(QSqlQuery &query, const QString &dbName)
{
    return exec(query, dbName);
}

QString DataBase::getCurrentDbName() const
{
    return currentDbName;
}

void DataBase::setCurrentDbName(const QString &value)
{
    if(!value.isEmpty())
    {
        currentDbName = value;
        database.setDatabaseName(currentDbName);
    }

}

DBDriverType DataBase::getType() const
{
    return type;
}

void DataBase::setType(const DBDriverType &value)
{
    type = value;
}

QString DataBase::getDriverName() const
{
    return driverName;
}

void DataBase::setDriverName(const QString &value)
{
    driverName = value;
}

bool DataBase::getConnected() const
{
    return connected;
}

void DataBase::setConnected(bool value)
{
    connected = value;
}

QSqlDatabase &DataBase::getDatabase()
{
    return database;
}

void DataBase::setDatabase(const QSqlDatabase &value)
{
    database = value;
}



} // namespace zsj
