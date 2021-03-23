#include "SQLiteDataBase.h"

#include <QMutex>
#include <QMutexLocker>
#include <QDebug>

#include "utils/Util.h"

namespace zsj
{

SQLiteDataBase::ptr SQLiteDataBase::sqliteDb;

SQLiteDataBase::SQLiteDataBase() :
    DataBase()
{

}

SQLiteDataBase::SQLiteDataBase(const QString &driverName,
                               const QString &defaultDbName,
                               zsj::DBDriverType type) :
    DataBase(driverName, defaultDbName, type)
{
    database = QSqlDatabase::addDatabase(driverName);
    database.setDatabaseName(defaultDbName);
    if(!database.open())
    {
        qCritical() << "Error: Failed to connect database."
                    << database.lastError();
        connected = false;
    }
    else
    {
        qInfo() << "Success to connect databse.";
        connected = true;
        QSqlQuery query(database);
        bool ret = query.exec(CreateTableCmd());
        if(!ret)
        {
            qCritical() << query.lastError();
        }
        else
        {
            qDebug() << "exec success";
        }
    }
}

SQLiteDataBase *SQLiteDataBase::Instance()
{
    if(sqliteDb.isNull())
    {
        static QMutex mutex;
        QMutexLocker lock(&mutex);
        if(sqliteDb.isNull())
        {
            sqliteDb.reset(new SQLiteDataBase);
        }
    }
    return sqliteDb.get();
}

SQLiteDataBase *SQLiteDataBase::Instance(const QString &driverName,
        const QString &defaultDbName,
        DBDriverType type)
{
    if(sqliteDb.isNull())
    {
        static QMutex mutex;
        QMutexLocker lock(&mutex);
        if(sqliteDb.isNull())
        {
            qDebug() << "new instance 3 args";
            sqliteDb.reset(new SQLiteDataBase(driverName, defaultDbName, type));
        }
    }
    return sqliteDb.get();
}

QString SQLiteDataBase::CreateTableCmd()
{
    return QString("CREATE TABLE IF NOT EXISTS "
                   "login_info( "
                   "id integer primary key Autoincrement, "
                   "head text not null,	"
                   "nickname text not null,	"
                   "account integer not null, "
                   "password text, "
                   "auto_login bool not null, "
                   "save_password bool not null,"
                   "last_update integer not null "
                   ");");
}

bool SQLiteDataBase::changeDataBase(const QString &dbName)
{
    if(dbName == getCurrentDbName())
    {
        return true;
    }
    database.close();
    database.setDatabaseName(dbName);
    if(!database.open())
    {
        qCritical() << "Error: Failed to connect database."
                    << database.lastError();
        connected = false;
        return false;
    }
    else
    {
        qInfo() << "Success to connect databse.";
        connected = true;
        setCurrentDbName(dbName);
        return true;
    }
}

SQLiteDataBase::~SQLiteDataBase()
{
    DESTRUCT_LOG_CRITICAL("deconstruct SQLiteDataBase");
}



} // namespace zsj
