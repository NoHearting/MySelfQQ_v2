/**
  * @file DataBase.h
  * @brief 数据库实例
  * @author zsj
  * @date 2021年3月17日11:05:25
  */
#pragma once

#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace zsj
{

enum class DBDriverType
{
    UNKNOW = 0,         // 未知
    SQLITE = 1,         // sqlite
    MYSQL,              // mysql
    SQLSERVER,          // sqlserver
    MONGODB,            // mongodb
    ORACLE              // oracle
};

class DataBase
{
public:
    /**
     * @brief DataBase
     * @param driverName 驱动名称
     * @param defaultDbName 数据库名称
     * @param type  数据库驱动类型
     */
    explicit DataBase(const QString &driverName,
                      const QString &defaultDbName,
                      DBDriverType type);
    DataBase();


    /**
     * @brief 改变当前操作的数据库
     * @param dbName    数据库名称
     * @return
     * @note 当前不可用
     */
    virtual bool changeDataBase(const QString & dbName) = 0;

    virtual ~DataBase();

    virtual bool selectQuery(QSqlQuery &query, const QString &dbName = "");

    virtual bool deleteQuery(QSqlQuery &query, const QString &dbName = "");

    virtual bool updateQuery(QSqlQuery &query, const QString &dbName = "");

    virtual bool insertQuery(QSqlQuery &query, const QString &dbName = "");





    QString getCurrentDbName() const;
    void setCurrentDbName(const QString &value);

    DBDriverType getType() const;
    void setType(const DBDriverType &value);

    QString getDriverName() const;
    void setDriverName(const QString &value);

    bool getConnected() const;
    void setConnected(bool value);

    QSqlDatabase &getDatabase();
    void setDatabase(const QSqlDatabase &value);


private:
    bool exec(QSqlQuery &query, const QString &dbName);
protected:
    QSqlDatabase database;      /// 数据库实例
    bool connected;             /// 是否连接


private:
    QString currentDbName;      /// 当前使用的数据库的名称
    DBDriverType type;          /// 驱动类型
    QString driverName;         /// 驱动名称

};

}

