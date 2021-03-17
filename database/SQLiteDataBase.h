#ifndef SQLITEDATABASE_H
#define SQLITEDATABASE_H

#include "database/DataBase.h"

#include <QScopedPointer>


namespace zsj
{



class SQLiteDataBase : public DataBase
{
public:
    typedef QScopedPointer<SQLiteDataBase> ptr;

    static SQLiteDataBase *Instance();
    static SQLiteDataBase *Instance(const QString &driverName,
                                    const QString &defaultDbName,
                                    DBDriverType type);
    static QString CreateTableCmd();

    /**
     * @brief changeDataBase
     * @param dbName
     * @return
     * @note 当前不可使用
     */
    virtual bool changeDataBase(const QString &dbName);

private:
    SQLiteDataBase();
    SQLiteDataBase(const QString &driverName,
                   const QString &defaultDbName,
                   DBDriverType type);

    static ptr sqliteDb;
};


} // namespace zsj

#endif // SQLITEDATABASE_H
